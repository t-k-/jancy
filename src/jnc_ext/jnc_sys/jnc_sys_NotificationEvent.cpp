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
#include "jnc_sys_NotificationEvent.h"
#include "jnc_sys_SysLib.h"
#include "jnc_Runtime.h"

namespace jnc {
namespace sys {

//..............................................................................

JNC_DEFINE_OPAQUE_CLASS_TYPE(
	NotificationEvent,
	"sys.NotificationEvent",
	g_sysLibGuid,
	SysLibCacheSlot_NotificationEvent,
	NotificationEvent,
	NULL
	)

JNC_BEGIN_TYPE_FUNCTION_MAP(NotificationEvent)
	JNC_MAP_CONSTRUCTOR(&jnc::construct<NotificationEvent>)
	JNC_MAP_DESTRUCTOR(&jnc::destruct<NotificationEvent>)
	JNC_MAP_FUNCTION("signal", &NotificationEvent::signal)
	JNC_MAP_FUNCTION("reset", &NotificationEvent::reset)
	JNC_MAP_FUNCTION("wait", &NotificationEvent::wait)
JNC_END_TYPE_FUNCTION_MAP()

//..............................................................................

bool
JNC_CDECL
NotificationEvent::wait(uint_t timeout)
{
	bool result;

	GcHeap* gcHeap = getCurrentThreadGcHeap();
	ASSERT(gcHeap);

	gcHeap->enterWaitRegion();
	result = m_event.wait(timeout);
	gcHeap->leaveWaitRegion();

	return result;
}

//..............................................................................

} // namespace sys
} // namespace jnc
