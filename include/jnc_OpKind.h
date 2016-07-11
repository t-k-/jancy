// This file is part of AXL (R) Library
// Tibbo Technology Inc (C) 2004-2013. All rights reserved
// Author: Vladimir Gladkov

#pragma once

typedef enum jnc_UnOpKind jnc_UnOpKind;
typedef enum jnc_BinOpKind jnc_BinOpKind;

//.............................................................................

enum jnc_UnOpKind
{
	jnc_UnOpKind_Undefined = 0,
	jnc_UnOpKind_Plus,
	jnc_UnOpKind_Minus,
	jnc_UnOpKind_BwNot,	
	jnc_UnOpKind_Addr,
	jnc_UnOpKind_Indir,	
	jnc_UnOpKind_LogNot,
	jnc_UnOpKind_PreInc,
	jnc_UnOpKind_PreDec,
	jnc_UnOpKind_PostInc,
	jnc_UnOpKind_PostDec,	
	jnc_UnOpKind_Ptr,
	jnc_UnOpKind__Count,
};

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

const char*
jnc_getUnOpKindString (jnc_UnOpKind opKind);

//.............................................................................

enum jnc_BinOpKind
{
	jnc_BinOpKind_Undefined = 0,
	
	// arithmetic
	
	jnc_BinOpKind_Add,
	jnc_BinOpKind_Sub,
	jnc_BinOpKind_Mul,
	jnc_BinOpKind_Div,
	jnc_BinOpKind_Mod,	
	jnc_BinOpKind_Shl,
	jnc_BinOpKind_Shr,	
	jnc_BinOpKind_BwAnd,
	jnc_BinOpKind_BwXor,	
	jnc_BinOpKind_BwOr,

	// special ops

	jnc_BinOpKind_At,
	jnc_BinOpKind_Idx,

	// comparison

	jnc_BinOpKind_Eq,
	jnc_BinOpKind_Ne,
	jnc_BinOpKind_Lt,
	jnc_BinOpKind_Le,
	jnc_BinOpKind_Gt,
	jnc_BinOpKind_Ge,

	// logic

	jnc_BinOpKind_LogAnd,
	jnc_BinOpKind_LogOr,

	// assignment

	jnc_BinOpKind_Assign,
	jnc_BinOpKind_RefAssign,
	jnc_BinOpKind_AddAssign,
	jnc_BinOpKind_SubAssign,
	jnc_BinOpKind_MulAssign,
	jnc_BinOpKind_DivAssign,
	jnc_BinOpKind_ModAssign,
	jnc_BinOpKind_ShlAssign,
	jnc_BinOpKind_ShrAssign,
	jnc_BinOpKind_AndAssign,
	jnc_BinOpKind_XorAssign,
	jnc_BinOpKind_OrAssign,
	jnc_BinOpKind_AtAssign,

	// meta

	jnc_BinOpKind__Count,
	jnc_BinOpKind__OpAssignDelta = jnc_BinOpKind_AddAssign - jnc_BinOpKind_Add,
};

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

const char*
jnc_getBinOpKindString (jnc_BinOpKind opKind);

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

#ifdef __cplusplus

namespace jnc {

//.............................................................................

enum UnOpKind
{
	UnOpKind_Undefined = jnc_UnOpKind_Undefined,
	UnOpKind_Plus      = jnc_UnOpKind_Plus,
	UnOpKind_Minus     = jnc_UnOpKind_Minus,
	UnOpKind_BwNot     = jnc_UnOpKind_BwNot,
	UnOpKind_Addr      = jnc_UnOpKind_Addr,
	UnOpKind_Indir     = jnc_UnOpKind_Indir,
	UnOpKind_LogNot    = jnc_UnOpKind_LogNot,
	UnOpKind_PreInc    = jnc_UnOpKind_PreInc,
	UnOpKind_PreDec    = jnc_UnOpKind_PreDec,
	UnOpKind_PostInc   = jnc_UnOpKind_PostInc,
	UnOpKind_PostDec   = jnc_UnOpKind_PostDec,
	UnOpKind_Ptr       = jnc_UnOpKind_Ptr,
	UnOpKind__Count    = jnc_UnOpKind__Count,
};

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

inline
const char*
getUnOpKindString (UnOpKind opKind)
{
	return jnc_getUnOpKindString ((jnc_UnOpKind) opKind);
}

//.............................................................................

enum BinOpKind
{
	BinOpKind_Undefined = jnc_BinOpKind_Undefined,
	BinOpKind_Add       = jnc_BinOpKind_Add,
	BinOpKind_Sub       = jnc_BinOpKind_Sub,
	BinOpKind_Mul       = jnc_BinOpKind_Mul,
	BinOpKind_Div       = jnc_BinOpKind_Div,
	BinOpKind_Mod       = jnc_BinOpKind_Mod,
	BinOpKind_Shl       = jnc_BinOpKind_Shl,
	BinOpKind_Shr       = jnc_BinOpKind_Shr,
	BinOpKind_BwAnd     = jnc_BinOpKind_BwAnd,
	BinOpKind_BwXor     = jnc_BinOpKind_BwXor,
	BinOpKind_BwOr      = jnc_BinOpKind_BwOr,
	BinOpKind_At        = jnc_BinOpKind_At,
	BinOpKind_Idx       = jnc_BinOpKind_Idx,
	BinOpKind_Eq        = jnc_BinOpKind_Eq,
	BinOpKind_Ne        = jnc_BinOpKind_Ne,
	BinOpKind_Lt        = jnc_BinOpKind_Lt,
	BinOpKind_Le        = jnc_BinOpKind_Le,
	BinOpKind_Gt        = jnc_BinOpKind_Gt,
	BinOpKind_Ge        = jnc_BinOpKind_Ge,
	BinOpKind_LogAnd    = jnc_BinOpKind_LogAnd,
	BinOpKind_LogOr     = jnc_BinOpKind_LogOr,
	BinOpKind_Assign    = jnc_BinOpKind_Assign,
	BinOpKind_RefAssign = jnc_BinOpKind_RefAssign,
	BinOpKind_AddAssign = jnc_BinOpKind_AddAssign,
	BinOpKind_SubAssign = jnc_BinOpKind_SubAssign,
	BinOpKind_MulAssign = jnc_BinOpKind_MulAssign,
	BinOpKind_DivAssign = jnc_BinOpKind_DivAssign,
	BinOpKind_ModAssign = jnc_BinOpKind_ModAssign,
	BinOpKind_ShlAssign = jnc_BinOpKind_ShlAssign,
	BinOpKind_ShrAssign = jnc_BinOpKind_ShrAssign,
	BinOpKind_AndAssign = jnc_BinOpKind_AndAssign,
	BinOpKind_XorAssign = jnc_BinOpKind_XorAssign,
	BinOpKind_OrAssign  = jnc_BinOpKind_OrAssign,
	BinOpKind_AtAssign  = jnc_BinOpKind_AtAssign,
	BinOpKind__Count    = jnc_BinOpKind__Count,
	BinOpKind__OpAssignDelta = jnc_BinOpKind__OpAssignDelta,
};

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

inline
const char*
getBinOpKindString (BinOpKind opKind)
{
	return jnc_getBinOpKindString ((jnc_BinOpKind) opKind);
}

//.............................................................................

} // namespace jnc

#endif // __cplusplus