// This file is part of AXL (R) Library
// Tibbo Technology Inc (C) 2004-2013. All rights reserved
// Author: Vladimir Gladkov

#pragma once

typedef enum jnc_BoxFlag jnc_BoxFlag;
typedef struct jnc_Box jnc_Box;
typedef struct jnc_DataPtrValidator jnc_DataPtrValidator;
typedef struct jnc_DataBox jnc_DataBox;
typedef struct jnc_StaticDataBox jnc_StaticDataBox;
typedef struct jnc_DynamicArrayBox jnc_DynamicArrayBox;
typedef struct jnc_DataPtr jnc_DataPtr;
typedef struct jnc_FunctionPtr jnc_FunctionPtr;
typedef struct jnc_PropertyPtr jnc_PropertyPtr;
typedef struct jnc_IfaceHdr jnc_IfaceHdr;
typedef struct jnc_Multicast jnc_Multicast;
typedef struct jnc_McSnapshot jnc_McSnapshot;
typedef struct jnc_ReactorBindSite jnc_ReactorBindSite;
typedef struct jnc_FmtLiteral jnc_FmtLiteral;
typedef struct jnc_Variant jnc_Variant;
typedef struct jnc_GcShadowStackFrame jnc_GcShadowStackFrame;
typedef struct jnc_GcMutatorThread jnc_GcMutatorThread;
typedef struct jnc_SjljFrame jnc_SjljFrame;
typedef struct jnc_Tls jnc_Tls;
typedef struct jnc_TlsVariableTable jnc_TlsVariableTable;
typedef struct jnc_ExceptionRecoverySnapshot jnc_ExceptionRecoverySnapshot;

//.............................................................................

// inheriting which works for both C and C++

#ifdef __cplusplus 
#	define JNC_BEGIN_INHERITED_STRUCT(Struct, BaseStruct) \
	struct Struct: BaseStruct {
#else
#	define JNC_BEGIN_INHERITED_STRUCT (Struct, BaseStruct) \
	struct Struct { BaseStruct;
#endif

#define JNC_END_INHERITED_STRUCT() \
	};

//.............................................................................

// when compiling core libraries, we want to use actual implementation classes
// as to avoid unncecessary casts; otherwise, use opaque struct pointers

#ifdef _JNC_CORE

namespace jnc {
namespace ct {

class Type;
class GcShadowStackFrameMap;

} // namespace ct

namespace rt {

class Runtime;
class GcHeap;

} // namespace rt
} // namespace jnc

typedef axl::sl::ListLink jnc_ListLink;
typedef jnc::ct::Type jnc_Type;
typedef jnc::ct::GcShadowStackFrameMap jnc_GcShadowStackFrameMap;
typedef jnc::rt::Runtime jnc_Runtime;

#else

typedef struct jnc_ListLink jnc_ListLink;
typedef struct jnc_Type jnc_Type;
typedef struct jnc_GcShadowStackFrameMap jnc_GcShadowStackFrameMap;
typedef struct jnc_Runtime jnc_Runtime;

struct jnc_ListLink
{
	jnc_ListLink* m_next;
	jnc_ListLink* m_prev;
};

#endif

//.............................................................................

// every class instance, every gc-allocated block and every static variable
// whose address has been used by a safe pointer needs a box

enum jnc_BoxFlag
{
	jnc_BoxFlag_WeakMark        = 0x01,
	jnc_BoxFlag_ClosureWeakMark = 0x02,
	jnc_BoxFlag_DataMark        = 0x04,
	jnc_BoxFlag_ClassMark       = 0x08,
	jnc_BoxFlag_Zombie          = 0x10,
	jnc_BoxFlag_StaticData      = 0x20,
	jnc_BoxFlag_DynamicArray    = 0x40,

	jnc_BoxFlag_MarkMask        = 0x0f,
};

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

struct jnc_Box
{
	jnc_Type* m_type;

	uintptr_t m_flags      : 8;

#if (_AXL_PTR_BITNESS == 64)
	uintptr_t m_rootOffset : 56;
#else
	uintptr_t m_rootOffset : 24; // more than enough
#endif
};

//.............................................................................

// structure backing up fat data pointer, e.g.:
// int* p;

struct jnc_DataPtr
{
	void* m_p;
	jnc_DataPtrValidator* m_validator;
};

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

// metainfo used for range checking, dynamic casts etc

struct jnc_DataPtrValidator
{
	jnc_Box* m_validatorBox;
	jnc_Box* m_targetBox;
	const void* m_rangeBegin;
	const void* m_rangeEnd;
};

//.............................................................................

// structure backing up fat function pointers, e.g.:
// int function* pfTest (int, int);
// int function weak* pfTest (int, int);

struct jnc_FunctionPtr
{
	void* m_p;
	jnc_IfaceHdr* m_closure;
};

//.............................................................................

// structure backing up property pointers, e.g.:
// int property* pxTest;
// int property weak* pxTest;

struct jnc_PropertyPtr
{
	void** m_vtable;
	jnc_IfaceHdr* m_closure;
};

//.............................................................................

// specialized boxes

JNC_BEGIN_INHERITED_STRUCT (jnc_DataBox, jnc_Box)
	jnc_DataPtrValidator m_validator;
JNC_END_INHERITED_STRUCT ()

JNC_BEGIN_INHERITED_STRUCT (jnc_StaticDataBox, jnc_Box)
	jnc_Box m_box;	
	void* m_p; // static data boxes are detached from the actual data
JNC_END_INHERITED_STRUCT ()

JNC_BEGIN_INHERITED_STRUCT (jnc_DynamicArrayBox, jnc_Box)
	union
	{
		size_t m_count;
		uint64_t m_padding; // ensure 8-byte alignment
	};

	jnc_DataPtrValidator m_validator; // when gcheap allocates validators, it re-uses this field
JNC_END_INHERITED_STRUCT ()

//.............................................................................

// header of class iface

struct jnc_IfaceHdr
{
	void* m_vtable;
	jnc_Box* m_box;

	// followed by parents, then by iface data fields
};

//.............................................................................

// structures backing up multicast, e.g.:
// mutlicast onFire ();

JNC_BEGIN_INHERITED_STRUCT (jnc_Multicast, jnc_IfaceHdr)
	volatile intptr_t m_lock;
	jnc_DataPtr m_ptr; // array of function closure, weak or unsafe pointers
	size_t m_count;
	size_t m_maxCount;
	void* m_handleTable;
JNC_END_INHERITED_STRUCT ()

//.............................................................................

// multicast snapshot returns function pointer with this closure:

JNC_BEGIN_INHERITED_STRUCT (jnc_McSnapshot, jnc_IfaceHdr)
	jnc_DataPtr m_ptr; // array of function closure or unsafe pointers
	size_t m_count;
JNC_END_INHERITED_STRUCT ()

//.............................................................................

// structure backing up reactor bind site in reactor class

struct jnc_ReactorBindSite
{
	jnc_IfaceHdr* m_onChanged;
	intptr_t m_cookie;
};

//.............................................................................

// structure backing up formatting literal

struct jnc_FmtLiteral
{
	jnc_DataPtr m_ptr;
	size_t m_length;
	size_t m_maxLength;
};

//.............................................................................

// structure backing up variants, e.g.:
// variant v;

struct jnc_Variant
{
	union 
	{
		int8_t m_int8;
		uint8_t m_uint8;
		int16_t m_int16;
		uint16_t m_uint16;
		int32_t m_int32;
		uint32_t m_uint32;
		int64_t m_int64;
		uint64_t m_uint64;
		intptr_t m_intptr;
		uintptr_t m_uintptr;

		float m_float;
		double m_double;

		void* m_p;
		jnc_IfaceHdr* m_classPtr;
		jnc_DataPtr m_dataPtr;
		jnc_FunctionPtr m_functionPtr;
		jnc_PropertyPtr m_propertyPtr;
	};

#if (_AXL_PTR_SIZE == 4)
	char m_padding [4]; // ensure the same layout regardless of pack factor
#endif

	jnc_Type* m_type;
};

//.............................................................................

struct jnc_GcShadowStackFrame
{
	jnc_GcShadowStackFrame* m_prev;
	jnc_GcShadowStackFrameMap* m_map;
	void** m_gcRootArray;         // stack array
	jnc_Type** m_gcRootTypeArray; // global array
};

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

JNC_BEGIN_INHERITED_STRUCT (jnc_GcMutatorThread, jnc_ListLink)
	uint64_t m_threadId;
	volatile bool m_isSafePoint;
	size_t m_waitRegionLevel;
	size_t m_noCollectRegionLevel;
	jnc_DataPtrValidator* m_dataPtrValidatorPoolBegin;
	jnc_DataPtrValidator* m_dataPtrValidatorPoolEnd;
JNC_END_INHERITED_STRUCT ()

//.............................................................................

struct jnc_SjljFrame
{
	jmp_buf m_jmpBuf;
};

//.............................................................................

JNC_BEGIN_INHERITED_STRUCT (jnc_Tls, jnc_ListLink)
	jnc_Tls* m_prev;
	jnc_Runtime* m_runtime;
	size_t m_initializeLevel;
	void* m_stackEpoch;
	jnc_GcMutatorThread m_gcMutatorThread;

	// followed by jnc_TlsVariableTable
JNC_END_INHERITED_STRUCT ()

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

struct jnc_TlsVariableTable
{
	jnc_SjljFrame* m_sjljFrame;
	jnc_GcShadowStackFrame* m_gcShadowStackTop;

	// followed by user-defined TLS variables 
};

//.............................................................................

struct jnc_ExceptionRecoverySnapshot
{
	size_t m_initializeLevel;
	size_t m_waitRegionLevel;
	size_t m_noCollectRegionLevel;
	jnc_GcShadowStackFrame* m_gcShadowStackTop;
	intptr_t m_result;
};

//.............................................................................

typedef 
void
jnc_StaticConstructFunc ();

typedef 
void
jnc_StaticDestructFunc ();

typedef 
void
jnc_DestructFunc (jnc_IfaceHdr* iface);

//.............................................................................

AXL_SELECT_ANY jnc_DataPtr g_jnc_nullPtr = { 0 };
AXL_SELECT_ANY jnc_FunctionPtr g_jnc_nullFunctionPtr = { 0 };
AXL_SELECT_ANY jnc_FunctionPtr g_jnc_nullPropertyPtr = { 0 };
AXL_SELECT_ANY jnc_Variant g_jnc_nullVariant = { 0 };

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

#ifdef __cplusplus

namespace jnc {

//.............................................................................

enum BoxFlag
{
	BoxFlag_WeakMark        = jnc_BoxFlag_WeakMark,
	BoxFlag_ClosureWeakMark = jnc_BoxFlag_ClosureWeakMark,
	BoxFlag_DataMark        = jnc_BoxFlag_DataMark,
	BoxFlag_ClassMark       = jnc_BoxFlag_ClassMark,
	BoxFlag_Zombie          = jnc_BoxFlag_Zombie,
	BoxFlag_StaticData      = jnc_BoxFlag_StaticData,
	BoxFlag_DynamicArray    = jnc_BoxFlag_DynamicArray,
	BoxFlag_MarkMask        = jnc_BoxFlag_MarkMask,
};

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

typedef jnc_Type Type;
typedef jnc_GcShadowStackFrameMap GcShadowStackFrameMap;
typedef jnc_Runtime Runtime;
typedef jnc_Box Box;
typedef jnc_DataPtrValidator DataPtrValidator;
typedef jnc_DataBox DataBox;
typedef jnc_StaticDataBox StaticDataBox;
typedef jnc_DynamicArrayBox DynamicArrayBox;
typedef jnc_DataPtr DataPtr;
typedef jnc_FunctionPtr FunctionPtr;
typedef jnc_PropertyPtr PropertyPtr;
typedef jnc_IfaceHdr IfaceHdr;
typedef jnc_Multicast Multicast;
typedef jnc_McSnapshot McSnapshot;
typedef jnc_ReactorBindSite ReactorBindSite;
typedef jnc_FmtLiteral FmtLiteral;
typedef jnc_Variant Variant;
typedef jnc_GcShadowStackFrame GcShadowStackFrame;
typedef jnc_GcMutatorThread GcMutatorThread;
typedef jnc_SjljFrame SjljFrame;
typedef jnc_Tls Tls;
typedef jnc_TlsVariableTable TlsVariableTable;
typedef jnc_ExceptionRecoverySnapshot ExceptionRecoverySnapshot;
typedef jnc_StaticConstructFunc StaticConstructFunc;
typedef jnc_StaticDestructFunc StaticDestructFunc;
typedef jnc_DestructFunc DestructFunc;

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

AXL_SELECT_ANY DataPtr g_nullPtr = { 0 };
AXL_SELECT_ANY jnc_FunctionPtr g_nullFunctionPtr = { 0 };
AXL_SELECT_ANY jnc_PropertyPtr g_nullPropertyPtr = { 0 };
AXL_SELECT_ANY jnc_Variant g_nullVariant = { 0 };

//.............................................................................

// iface inside a box

// since in C++03 we can't get alignof (T), we need to provide multiple boxes for
// all kinds of alignments (1, 2, 4, 8)

template <typename T>
class ClassBoxBase: public Box
{
public:
	T* p ()
	{
		return (T*) (this + 1);
	}

	operator T* ()
	{
		return p ();
	}

	T* operator -> ()
	{
		return p ();
	}
};

#pragma pack (push, 1)

template <typename T>
class ClassBox_align1: public ClassBoxBase <T>
{
protected:
	char m_buffer [sizeof (T)];
} AXL_GCC_MSC_STRUCT;

#pragma pack (2)

template <typename T>
class ClassBox_align2: public ClassBoxBase <T>
{
protected:
	char m_buffer [sizeof (T)];
} AXL_GCC_MSC_STRUCT;

#pragma pack (4)

template <typename T>
class ClassBox_align4: public ClassBoxBase <T>
{
protected:
	char m_buffer [sizeof (T)];
} AXL_GCC_MSC_STRUCT;

#pragma pack (8)

template <typename T>
class ClassBox_align8: public ClassBoxBase <T>
{
protected:
#if (_AXL_PTR_SIZE == 8) // 8-byte alignment will be forced by Box/IfaceHdr
	char m_buffer [sizeof (T)];
#else
	union
	{
		char m_buffer [sizeof (T)];
		int64_t m_align8; // otherwise, we need an 8-byte field
	} AXL_GCC_MSC_STRUCT;
#endif
} AXL_GCC_MSC_STRUCT;

#pragma pack (pop)

// default alignment

template <typename T>
class ClassBox: public ClassBoxBase <T>
{
protected:
	char m_buffer [sizeof (T)];
};

//.............................................................................

} // namespace jnc

#endif // __cplusplus