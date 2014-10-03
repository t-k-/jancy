// This file is part of AXL (R) Library
// Tibbo Technology Inc (C) 2004-2013. All rights reserved
// Author: Vladimir Gladkov

#pragma once

#include "jnc_ImportType.h"
#include "jnc_DataPtrType.h"

namespace jnc {

//.............................................................................

enum ArrayTypeFlag
{
	ArrayTypeFlag_AutoSize = 0x010000,
};

//.............................................................................

class ArrayType: public Type
{
	friend class TypeMgr;
	friend class Parser;

protected:
	Type* m_elementType;
	ImportType* m_elementType_i;
	Type* m_rootType;
	size_t m_elementCount;

	rtl::BoxList <Token> m_elementCountInitializer;
	Unit* m_parentUnit;
	Namespace* m_parentNamespace;

public:
	ArrayType ();

	Type*
	getElementType ()
	{
		return m_elementType;
	}

	ImportType*
	getElementType_i ()
	{
		return m_elementType_i;
	}

	Type*
	getRootType ();

	size_t
	getElementCount ()
	{
		return m_elementCount;
	}

	rtl::ConstBoxList <Token>
	getElementCountInitializer ()
	{
		return m_elementCountInitializer;
	}

	static
	rtl::String
	createSignature (
		Type* elementType,
		size_t elementCount
		)
	{
		return rtl::String::format_s (
			"A%d%s",
			elementCount,
			elementType->getSignature ().cc () // thanks a lot gcc
			);
	}

	virtual
	void
	gcMark (
		Runtime* runtime,
		void* p
		);


protected:
	virtual
	bool
	calcLayout ();

	virtual
	void
	prepareTypeString ();

	virtual
	void
	prepareLlvmType ()
	{
		ASSERT (m_elementCount != -1);
		m_llvmType = llvm::ArrayType::get (m_elementType->getLlvmType (), m_elementCount);
	}

	virtual
	void
	prepareLlvmDiType ();
};

//.............................................................................

inline
bool
isAutoSizeArrayType (Type* type)
{
	return
		type->getTypeKind () == TypeKind_Array &&
		(type->getFlags () & ArrayTypeFlag_AutoSize) != 0;
}

inline
bool
isCharArrayType (Type* type)
{
	return
		type->getTypeKind () == TypeKind_Array &&
		((ArrayType*) type)->getElementType ()->getTypeKind () == TypeKind_Char;
}

inline
bool
isCharArrayRefType (Type* type)
{
	return
		type->getTypeKind () == TypeKind_DataRef &&
		isCharArrayType (((DataPtrType*) type)->getTargetType ());
}

//.............................................................................

} // namespace jnc {
