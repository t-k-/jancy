//..............................................................................
//
//  This file is part of the Jancy toolkit.
//
//  Jancy is distributed under the MIT license.
//  For details see accompanying license.txt file,
//  the public copy of which is also available at:
//  http://tibbo.com/downloads/archive/jancy/license.txt
//
//..............................................................................

#include "pch.h"
#include "jnc_io_HostNameResolver.h"
#include "jnc_io_IoLib.h"

namespace jnc {
namespace io {

//..............................................................................

JNC_DEFINE_OPAQUE_CLASS_TYPE(
	HostNameResolver,
	"io.HostNameResolver",
	g_ioLibGuid,
	IoLibCacheSlot_HostNameResolver,
	HostNameResolver,
	&HostNameResolver::markOpaqueGcRoots
	)

JNC_BEGIN_TYPE_FUNCTION_MAP(HostNameResolver)
	JNC_MAP_CONSTRUCTOR(&jnc::construct<HostNameResolver>)
	JNC_MAP_DESTRUCTOR(&jnc::destruct<HostNameResolver>)
	JNC_MAP_FUNCTION("resolve", &HostNameResolver::resolve)
	JNC_MAP_FUNCTION("cancel", &HostNameResolver::cancel)
	JNC_MAP_FUNCTION("close", &HostNameResolver::close)
	JNC_MAP_FUNCTION("wait", &HostNameResolver::wait)
	JNC_MAP_FUNCTION("cancelWait", &HostNameResolver::cancelWait)
	JNC_MAP_FUNCTION("blockingWait", &HostNameResolver::blockingWait)
JNC_END_TYPE_FUNCTION_MAP()

//..............................................................................

bool
JNC_CDECL
HostNameResolver::resolve(
	DataPtr namePtr,
	uint16_t addrFamily
	)
{
	cancel();

	const char* name = (const char*)namePtr.m_p;

	axl::io::SockAddr sockAddr;
	bool result = sockAddr.parse(name);
	if (result)
	{
		complete(&sockAddr, 1);
		return true;
	}

	sl::String nameString;
	uint_t port;

	const char* p = strchr(name, ':');
	if (!p)
	{
		nameString = name;
		port = 0;
	}
	else
	{
		char* end;
		port = (ushort_t)strtol(p + 1, &end, 10);
		if (end == p)
		{
			setIoErrorEvent("invalid port string");
			return false;
		}

		nameString.copy(name, p - name);
	}

	m_lock.lock();
	m_name = nameString;
	m_addrFamily = addrFamily;
	m_port = sl::swapByteOrder16(port);

	if (m_ioThreadFlags & IoThreadFlag_Started)
	{
		wakeIoThread();
		m_lock.unlock();
		return true;
	}

	m_ioThreadFlags |= IoThreadFlag_Started;
	m_activeEvents = 0;
	m_lock.unlock();

	AsyncIoBase::open();
	m_ioThread.start();
	return true;
}

void
JNC_CDECL
HostNameResolver::cancel()
{
	m_lock.lock();
	m_name.clear();
	// currently, no need to wakeIoThread() -- ::getaddrinfo is not cancellable anyway
	// later, at least on Windows, we may switch to the cancellable ::GetAddrInfoEx
	m_activeEvents = 0;
	m_lock.unlock();
}

void
JNC_CDECL
HostNameResolver::close()
{
	m_lock.lock();
	m_name.clear();
	m_ioThreadFlags |= IoThreadFlag_Closing;
	m_ioThreadFlags &= ~IoThreadFlag_Started;
	m_activeEvents = 0;
	wakeIoThread();
	m_lock.unlock();

	GcHeap* gcHeap = m_runtime->getGcHeap();
	gcHeap->enterWaitRegion();
	m_ioThread.waitAndClose();
	gcHeap->leaveWaitRegion();

	AsyncIoBase::close();
}

void
HostNameResolver::ioThreadFunc()
{
	sl::String name;
	uint_t addrFamily;
	uint_t port;

	wakeIoThread();

	for (;;)
	{
		sleepIoThread();

		m_lock.lock();
		if (m_ioThreadFlags & IoThreadFlag_Closing)
		{
			m_lock.unlock();
			break;
		}

		if (m_name.isEmpty())
		{
			m_lock.unlock();
			continue;
		}

		name = m_name;
		addrFamily = m_addrFamily;
		port = m_port;
		m_lock.unlock();

		sl::Array<axl::io::SockAddr> addrArray;
		bool result = axl::io::resolveHostName(&addrArray, name, addrFamily);

		m_lock.lock();
		if (m_ioThreadFlags & IoThreadFlag_Closing)
		{
			m_lock.unlock();
			break;
		}

		if (name != m_name ||
			addrFamily != m_addrFamily ||
			port != m_port)
		{
			m_lock.unlock(); // cancelled
		}
		else if (!result)
		{
			setIoErrorEvent_l();
		}
		else
		{
			size_t count = addrArray.getCount();
			for (size_t i = 0; i < count; i++)
				addrArray[i].m_addr_ip4.sin_port = port;

			complete_l(addrArray, count);
		}
	}
}

void
HostNameResolver::complete_l(
	const axl::io::SockAddr* addressTable,
	size_t count
	)
{
	JNC_BEGIN_CALL_SITE(m_runtime)
	m_addressTablePtr = memDup(addressTable, count * sizeof(axl::io::SockAddr));
	m_addressCount = count;
	JNC_END_CALL_SITE()

	setEvents_l(HostNameResolverEvent_Resolved);
}

//..............................................................................

} // namespace io
} // namespace jnc