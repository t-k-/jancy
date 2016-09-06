#pragma once

#include "axl_g_Pch.h"

#if (_AXL_ENV == AXL_ENV_WIN)
#	define socklen_t    int
#	include <io.h>
#	include <fcntl.h>

#elif (_AXL_ENV == AXL_ENV_POSIX)
#	include <sys/socket.h>
#	include <netinet/in.h>
#	include <netinet/ip.h>
#	include <arpa/inet.h>
#	define SOCKET         int
#	define INVALID_SOCKET (-1)
#	define closesocket    close

#endif

//.............................................................................

// Jancy

#include "jnc_Module.h"
#include "jnc_Runtime.h"
#include "jnc_CallSite.h"
#include "jnc_ExtensionLib.h"

// AXL

#include "axl_sl_CmdLineParser.h"
#include "axl_sl_Singleton.h"
#include "axl_sl_BoxList.h"
#include "axl_sys_Time.h"
#include "axl_io_FilePathUtils.h"
#include "axl_io_FileEnumerator.h"

using namespace axl;

//.............................................................................
