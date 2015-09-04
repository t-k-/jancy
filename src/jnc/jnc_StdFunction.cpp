#include "pch.h"
#include "jnc_StdFunction.h"
#include "jnc_Module.h"

namespace jnc {

//.............................................................................

const char*
getStdFunctionName (StdFunc stdFunction)
{
	const char* nameTable [StdFunc__Count] =
	{
		NULL,                  // StdFunc_DynamicSizeOf,
		NULL,                  // StdFunc_DynamicCountOf,
		NULL,                  // StdFunc_DynamicCastDataPtr,
		NULL,                  // StdFunc_DynamicCastClassPtr,
		NULL,                  // StdFunc_DynamicCastVariant,
		NULL,                  // StdFunc_StrengthenClassPtr,

		NULL,                  // StdFunc_PrimeStaticClass,
		NULL,                  // StdFunc_TryAllocateClass,
		NULL,                  // StdFunc_AllocateClass,
		NULL,                  // StdFunc_TryAllocateData,
		NULL,                  // StdFunc_AllocateData,
		NULL,                  // StdFunc_TryAllocateArray,
		NULL,                  // StdFunc_AllocateArray,
		NULL,                  // StdFunc_CreateDataPtrValidator,
		
		"collectGarbage",      // StdFunc_RunGc,
		"getCurrentThreadId",  // StdFunc_GetCurrentThreadId,
		"createThread",        // StdFunc_CreateThread,
		"sleep",               // StdFunc_Sleep,
		"getTimestamp",        // StdFunc_GetTimestamp,
		"format",              // StdFunc_Format,
		"strlen",              // StdFunc_StrLen,
		"strcmp",              // StdFunc_StrCmp,
		"stricmp",             // StdFunc_StriCmp,
		"strchr",              // StdFunc_StrChr,
		"strcat",              // StdFunc_StrCat,
		"strdup",              // StdFunc_StrDup,
		"memcmp",              // StdFunc_MemCmp,
		"memchr",              // StdFunc_MemChr,
		"memcpy",              // StdFunc_MemCpy,
		"memset",              // StdFunc_MemSet,
		"memcat",              // StdFunc_MemCat,
		"memdup",              // StdFunc_MemDup,
		"rand",                // StdFunc_Rand,
		"printf",              // StdFunc_Printf,
		"atoi",                // StdFunc_Atoi,
		NULL,                  // StdFunc_GetTls,

		NULL,                  // StdFunc_AppendFmtLiteral_a,
		NULL,                  // StdFunc_AppendFmtLiteral_p,
		NULL,                  // StdFunc_AppendFmtLiteral_i32,
		NULL,                  // StdFunc_AppendFmtLiteral_ui32,
		NULL,                  // StdFunc_AppendFmtLiteral_i64,
		NULL,                  // StdFunc_AppendFmtLiteral_ui64,
		NULL,                  // StdFunc_AppendFmtLiteral_f,
		NULL,                  // StdFunc_AppendFmtLiteral_v,
		NULL,                  // StdFunc_AppendFmtLiteral_s,
		NULL,                  // StdFunc_AppendFmtLiteral_sr,
		NULL,                  // StdFunc_AppendFmtLiteral_cb,
		NULL,                  // StdFunc_AppendFmtLiteral_cbr,
		NULL,                  // StdFunc_AppendFmtLiteral_br,
		NULL,                  // StdFunc_SimpleMulticastCall,
		
		"throw",               // StdFunc_Throw,
		"getLastError",        // StdFunc_GetLastError,
		"setPosixError",       // StdFunc_SetPosixError,
		"setStringError",      // StdFunc_SetStringError,
		"assertionFailure",    // StdFunc_AssertionFailure,
		"addStaticDestructor", // StdFunc_AddStaticDestructor,
		"addStaticClassDestructor", // StdFunc_AddStaticClassDestructor,
		
		NULL,                  // StdFunc_TryCheckDataPtrRangeDirect,
		NULL,                  // StdFunc_CheckDataPtrRangeDirect,
		NULL,                  // StdFunc_TryCheckDataPtrRangeIndirect,
		NULL,                  // StdFunc_CheckDataPtrRangeIndirect,
		NULL,                  // StdFunc_TryCheckNullPtr,
		NULL,                  // StdFunc_CheckNullPtr,
		NULL,                  // StdFunc_CheckStackOverflow,
		NULL,                  // StdFunc_TryLazyGetLibraryFunction,
		NULL,                  // StdFunc_LazyGetLibraryFunction,

		NULL,                  // StdFunc_LlvmMemcpy,
		NULL,                  // StdFunc_LlvmMemmove,
		NULL,                  // StdFunc_LlvmMemset,
	};

	ASSERT ((size_t) stdFunction < StdFunc__Count);
	return nameTable [stdFunction];
}

const StdItemSource*
getStdFunctionSource (StdFunc stdFunction)
{
	#include "jnc_StdFunctions.jnc.cpp"

	static StdItemSource sourceTable [StdFunc__Count] =
	{
		{                                        // StdFunc_DynamicSizeOf,
			dynamicSizeOfSrc,
			lengthof (dynamicSizeOfSrc),
			StdNamespace_Internal,
		},
		{                                        // StdFunc_DynamicCountOf,
			dynamicCountOfSrc,
			lengthof (dynamicCountOfSrc),
			StdNamespace_Internal,
		},
		{                                        // StdFunc_DynamicCastDataPtr,
			dynamicCastDataPtrSrc,
			lengthof (dynamicCastDataPtrSrc),
			StdNamespace_Internal,
		},
		{                                        // StdFunc_DynamicCastClassPtr,
			dynamicCastClassPtrSrc,
			lengthof (dynamicCastClassPtrSrc),
			StdNamespace_Internal,
		},
		{                                       // StdFunc_DynamicCastVariant,
			dynamicCastVariantSrc,
			lengthof (dynamicCastVariantSrc),
			StdNamespace_Internal,
		},
		{                                        // StdFunc_StrengthenClassPtr,
			strengthenClassPtrSrc,
			lengthof (strengthenClassPtrSrc),
			StdNamespace_Internal,
		},

		{ NULL },                                // StdFunc_PrimeStaticClass,
		{ NULL },                                // StdFunc_TryAllocateClass,
		{ NULL },                                // StdFunc_AllocateClass,
		{ NULL },                                // StdFunc_TryAllocateData,
		{ NULL },                                // StdFunc_AllocateData,
		{ NULL },                                // StdFunc_TryAllocateArray,
		{ NULL },                                // StdFunc_AllocateArray,
		{ NULL },                                // StdFunc_CreateDataPtrValidator,

		{                                        // StdFunc_CollectGarbage,
			collectGarbageSrc,
			lengthof (collectGarbageSrc),
			StdNamespace_Jnc,
		},
		{                                        // StdFunc_GetCurrentThreadId,
			getCurrentThreadIdSrc,
			lengthof (getCurrentThreadIdSrc),
			StdNamespace_Jnc,
		},
		{                                        // StdFunc_CreateThread,
			createThreadSrc,
			lengthof (createThreadSrc),
			StdNamespace_Jnc,
		},
		{                                        // StdFunc_Sleep,
			sleepSrc,
			lengthof (sleepSrc),
			StdNamespace_Jnc,
		},
		{                                        // StdFunc_GetTimestamp,
			getTimestampSrc,
			lengthof (getTimestampSrc),
			StdNamespace_Jnc,
		},
		{                                        // StdFunc_Format,
			formatSrc,
			lengthof (formatSrc),
			StdNamespace_Jnc,
		},
		{                                        // StdFunc_StrLen,
			strlenSrc,
			lengthof (strlenSrc),
			StdNamespace_Global,
		},
		{                                        // StdFunc_StrCmp,
			strcmpSrc,
			lengthof (strcmpSrc),
			StdNamespace_Global,
		},
		{                                        // StdFunc_StriCmp,
			stricmpSrc,
			lengthof (stricmpSrc),
			StdNamespace_Global,
		},
		{                                        // StdFunc_StrChr,
			strchrSrc,
			lengthof (strchrSrc),
			StdNamespace_Global,
		},
		{                                        // StdFunc_StrCat,
			strcatSrc,
			lengthof (strcatSrc),
			StdNamespace_Global,
		},
		{                                        // StdFunc_StrDup,
			strdupSrc,
			lengthof (strdupSrc),
			StdNamespace_Global,
		},
		{                                        // StdFunc_MemCmp,
			memcmpSrc,
			lengthof (memcmpSrc),
			StdNamespace_Global,
		},
		{                                        // StdFunc_MemChr,
			memchrSrc,
			lengthof (memchrSrc),
			StdNamespace_Global,
		},
		{                                        // StdFunc_MemCpy,
			memcpySrc,
			lengthof (memcpySrc),
			StdNamespace_Global,
		},
		{                                        // StdFunc_MemSet,
			memsetSrc,
			lengthof (memsetSrc),
			StdNamespace_Global,
		},
		{                                        // StdFunc_MemCat,
			memcatSrc,
			lengthof (memcatSrc),
			StdNamespace_Global,
		},
		{                                        // StdFunc_MemDup,
			memdupSrc,
			lengthof (memdupSrc),
			StdNamespace_Global,
		},
		{                                        // StdFunc_Rand,
			randSrc,
			lengthof (randSrc),
			StdNamespace_Global,
		},
		{                                        // StdFunc_Printf,
			printfSrc,
			lengthof (printfSrc),
			StdNamespace_Global,
		},
		{                                        // StdFunc_Atoi,
			atoiSrc,
			lengthof (atoiSrc),
			StdNamespace_Global,
		},
		{ NULL },                                // StdFunc_GetTls,
		{                                        // StdFunc_AppendFmtLiteral_a,
			appendFmtLiteralSrc_a,
			lengthof (appendFmtLiteralSrc_a),
			StdNamespace_Internal,
		},
		{                                        // StdFunc_AppendFmtLiteral_p,
			appendFmtLiteralSrc_p,
			lengthof (appendFmtLiteralSrc_p),
			StdNamespace_Internal,
		},
		{                                        // StdFunc_AppendFmtLiteral_i32,
			appendFmtLiteralSrc_i32,
			lengthof (appendFmtLiteralSrc_i32),
			StdNamespace_Internal,
		},
		{                                        // StdFunc_AppendFmtLiteral_ui32,
			appendFmtLiteralSrc_ui32,
			lengthof (appendFmtLiteralSrc_ui32),
			StdNamespace_Internal,
		},
		{                                        // StdFunc_AppendFmtLiteral_i64,
			appendFmtLiteralSrc_i64,
			lengthof (appendFmtLiteralSrc_i64),
			StdNamespace_Internal,
		},
		{                                        // StdFunc_AppendFmtLiteral_ui64,
			appendFmtLiteralSrc_ui64,
			lengthof (appendFmtLiteralSrc_ui64),
			StdNamespace_Internal,
		},
		{                                       // StdFunc_AppendFmtLiteral_f,
			appendFmtLiteralSrc_f,
			lengthof (appendFmtLiteralSrc_f),
			StdNamespace_Internal,
		},
		{                                       // StdFunc_AppendFmtLiteral_v,
			appendFmtLiteralSrc_v,
			lengthof (appendFmtLiteralSrc_v),
			StdNamespace_Internal,
		},
		{                                       // StdFunc_AppendFmtLiteral_s,
			appendFmtLiteralSrc_s,
			lengthof (appendFmtLiteralSrc_s),
			StdNamespace_Internal,
		},
		{                                       // StdFunc_AppendFmtLiteral_sr,
			appendFmtLiteralSrc_sr,
			lengthof (appendFmtLiteralSrc_sr),
			StdNamespace_Internal,
		},
		{                                       // StdFunc_AppendFmtLiteral_cb,
			appendFmtLiteralSrc_cb,
			lengthof (appendFmtLiteralSrc_cb),
			StdNamespace_Internal,
		},
		{                                       // StdFunc_AppendFmtLiteral_cbr,
			appendFmtLiteralSrc_cbr,
			lengthof (appendFmtLiteralSrc_cbr),
			StdNamespace_Internal,
		},
		{                                       // StdFunc_AppendFmtLiteral_br,
			appendFmtLiteralSrc_br,
			lengthof (appendFmtLiteralSrc_br),
			StdNamespace_Internal,
		},
		{ NULL },                               // StdFunc_SimpleMulticastCall,
		{                                       // StdFunc_Throw,
			throwSrc,
			lengthof (throwSrc),
			StdNamespace_Jnc,
		},
		{                                       // StdFunc_GetLastError,
			getLastErrorSrc,
			lengthof (getLastErrorSrc),
			StdNamespace_Jnc,
		},
		{                                       // StdFunc_SetPosixError,
			setPosixErrorSrc,
			lengthof (setPosixErrorSrc),
			StdNamespace_Jnc,
		},
		{                                       // StdFunc_SetStringError,
			setStringErrorSrc,
			lengthof (setStringErrorSrc),
			StdNamespace_Jnc,
		},
		{                                       // StdFunc_AssertionFailure,
			assertionFailureSrc,
			lengthof (assertionFailureSrc),
			StdNamespace_Internal,
		},
		{                                       // StdFunc_AddStaticDestructor,
			addStaticDestructorSrc,
			lengthof (addStaticDestructorSrc),
			StdNamespace_Internal,
		},
		{                                       // StdFunc_AddStaticClassDestructor,
			addStaticClassDestructorSrc,
			lengthof (addStaticClassDestructorSrc),
			StdNamespace_Internal,
		},
		{                                       // StdFunc_TryCheckDataPtrRangeDirect,
			tryCheckDataPtrRangeDirectSrc,
			lengthof (tryCheckDataPtrRangeDirectSrc),
			StdNamespace_Internal,
		},
		{                                       // StdFunc_CheckDataPtrRangeDirect,
			checkDataPtrRangeDirectSrc,
			lengthof (checkDataPtrRangeDirectSrc),
			StdNamespace_Internal,
		},
		{ NULL },                               // StdFunc_TryCheckDataPtrRangeIndirect,
		{ NULL },                               // StdFunc_CheckDataPtrRangeIndirect,
		{                                       // StdFunc_TryCheckNullPtr,
			tryCheckNullPtrSrc,
			lengthof (tryCheckNullPtrSrc),
			StdNamespace_Internal,
		},
		{                                       // StdFunc_CheckNullPtr,
			checkNullPtrSrc,
			lengthof (checkNullPtrSrc),
			StdNamespace_Internal,
		},
		{                                       // StdFunc_CheckStackOverflow,
			checkStackOverflowSrc,
			lengthof (checkStackOverflowSrc),
			StdNamespace_Internal,
		},
		{                                       // StdFunc_TryLazyGetLibraryFunctionAddr,
			tryLazyGetLibraryFunctionSrc,
			lengthof (tryLazyGetLibraryFunctionSrc),
			StdNamespace_Internal,
		},
		{                                       // StdFunc_LazyGetLibraryFunctionAddr,
			lazyGetLibraryFunctionSrc,
			lengthof (lazyGetLibraryFunctionSrc),
			StdNamespace_Internal,
		},
		{ NULL },                              // StdFunc_LlvmMemcpy
		{ NULL },                              // StdFunc_LlvmMemmove
		{ NULL },                              // StdFunc_LlvmMemset
	};

	ASSERT ((size_t) stdFunction < StdFunc__Count);
	return &sourceTable [stdFunction];
}

//.............................................................................
	
ModuleItem*
LazyStdFunction::getActualItem ()
{
	return m_module->m_functionMgr.getStdFunction (m_func);
}

//.............................................................................

} // namespace jnc {