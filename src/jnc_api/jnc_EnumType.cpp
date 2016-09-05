#include "pch.h"
#include "jnc_ArrayType.h"

#ifdef _JNC_DYNAMIC_EXTENSION_LIB
#	include "jnc_DynamicExtensionLibHost.h"
#	include "jnc_ExtensionLib.h"
#elif defined (_JNC_CORE)
#	include "jnc_rt_Runtime.h"
#	include "jnc_ct_Module.h"
#endif

//.............................................................................

#ifdef _JNC_DYNAMIC_EXTENSION_LIB

JNC_EXTERN_C
int64_t
jnc_EnumConst_getValue (jnc_EnumConst* enumConst)
{
	return jnc_g_dynamicExtensionLibHost->m_enumConstFuncTable->m_getValueFunc (enumConst);
}

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

JNC_EXTERN_C
jnc_Type*
jnc_EnumType_getBaseType (jnc_EnumType* type)
{
	return jnc_g_dynamicExtensionLibHost->m_enumTypeFuncTable->m_getBaseTypeFunc (type);
}

JNC_EXTERN_C
size_t
jnc_EnumType_getConstCount (jnc_EnumType* type)
{
	return jnc_g_dynamicExtensionLibHost->m_enumTypeFuncTable->m_getConstCountFunc (type);
}

JNC_EXTERN_C
jnc_EnumConst*
jnc_EnumType_getConst (
	jnc_EnumType* type,
	size_t index
	)
{
	return jnc_g_dynamicExtensionLibHost->m_enumTypeFuncTable->m_getConstFunc (type, index);
}

#else // _JNC_DYNAMIC_EXTENSION_LIB

JNC_EXTERN_C
int64_t
jnc_EnumConst_getValue (jnc_EnumConst* enumConst)
{
	return enumConst->getValue ();
}

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

JNC_EXTERN_C
jnc_Type*
jnc_EnumType_getBaseType (jnc_EnumType* type)
{
	return type->getBaseType ();
}

JNC_EXTERN_C
size_t
jnc_EnumType_getConstCount (jnc_EnumType* type)
{
	return type->getConstArray ().getCount ();
}

JNC_EXTERN_C
jnc_EnumConst*
jnc_EnumType_getConst (
	jnc_EnumType* type,
	size_t index
	)
{
	return type->getConstArray () [index];
}

#endif // _JNC_DYNAMIC_EXTENSION_LIB

//.............................................................................