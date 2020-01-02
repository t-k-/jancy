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

#pragma once

#include "jnc_io_FileStream.h"

namespace jnc {
namespace io {

JNC_DECLARE_OPAQUE_CLASS_TYPE(ChildProcess)

//..............................................................................

enum ChildProcessFlag
{
	ChildProcessFlag_MergeStdoutStderr = 0x01
};

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

class ChildProcess: IfaceHdr
{
public:
	JNC_DECLARE_CLASS_TYPE_STATIC_METHODS(ChildProcess)

public:
	bool m_isOpen;

	ClassBox<FileStream> m_stdin;
	ClassBox<FileStream> m_stdout;
	ClassBox<FileStream> m_stderr;

protected:
#if (_JNC_OS_WIN)
	sys::win::Process m_process;
#else
	pid_t m_pid;
#endif

public:
	ChildProcess();
	~ChildProcess();

	uint_t
	JNC_CDECL
	getExitCode();

	bool
	JNC_CDECL
	start(
		DataPtr commandLinePtr,
		uint_t flags
		);

	void
	JNC_CDECL
	close();

	bool
	JNC_CDECL
	wait(uint_t timeout);

	void
	JNC_CDECL
	waitAndClose(uint_t timeout);

	bool
	JNC_CDECL
	terminate();

protected:
#if (_JNC_OS_WIN)
	typedef axl::io::win::File AxlOsFile;
#else
	typedef axl::io::psx::File AxlOsFile;
#endif
	void
	attachFileStream(
		io::FileStream* fileStream,
		AxlOsFile* file
		);
};

//..............................................................................

} // namespace io
} // namespace jnc
