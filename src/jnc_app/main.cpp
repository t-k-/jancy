#include "pch.h"
#include "Jnc.h"
#include "version.h"

#define _JNCC_PRINT_USAGE_IF_NO_ARGUMENTS

//.............................................................................

void
printVersion (OutStream* outStream)
{
	outStream->printf (
		"Jancy v%d.%d.%d (%s%s)\n",
		VERSION_MAJOR,
		VERSION_MINOR,
		VERSION_REVISION,
		_AXL_CPU_STRING,
		_AXL_DEBUG_SUFFIX
		);
}

void
printUsage (OutStream* outStream)
{
	printVersion (outStream);

	sl::String helpString = CmdLineSwitchTable::getHelpString ();
	outStream->printf ("Usage: jancy [<options>...] <source_file>\n%s", helpString.cc ());
}

//.............................................................................

#if (_AXL_ENV == AXL_ENV_WIN)
int
wmain (
	int argc,
	wchar_t* argv []
	)
#else
int
main (
	int argc,
	char* argv []
	)
#endif
{
	bool result;

	llvm::InitializeNativeTarget ();
	llvm::InitializeNativeTargetAsmParser ();
	llvm::InitializeNativeTargetAsmPrinter ();
	llvm::InitializeNativeTargetDisassembler ();

	lex::registerParseErrorProvider ();
	srand ((int) sys::getTimestamp ());

	FileOutStream stdOut;
	CmdLine cmdLine;
	CmdLineParser parser (&cmdLine);

#ifdef _JNCC_PRINT_USAGE_IF_NO_ARGUMENTS
	if (argc < 2)
	{
		printUsage (&stdOut);
		return 0;
	}
#endif

	result = parser.parse (argc, argv);
	if (!result)
	{
		printf ("error parsing command line: %s\n", err::getLastErrorDescription ().cc ());
		return JncError_InvalidCmdLine;
	}

	Jnc jnc;
	return jnc.run (&cmdLine, &stdOut);
}

//.............................................................................
