/*****************************************************************************
** Copyright (C) 2015 Intel Corporation.                                    **
**                                                                          **
** Licensed under the Apache License, Version 2.0 (the "License");          **
** you may not use this file except in compliance with the License.         **
** You may obtain a copy of the License at                                  **
**                                                                          **
**      http://www.apache.org/licenses/LICENSE-2.0                          **
**                                                                          **
** Unless required by applicable law or agreed to in writing, software      **
** distributed under the License is distributed on an "AS IS" BASIS,        **
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. **
** See the License for the specific language governing permissions and      **
** limitations under the License.                                           **
*****************************************************************************/

#include "cryptoki.h"
#include "hal.h"

static CK_RV get_or_set_object_attr(uint32_t command_id,
                                    CK_SESSION_HANDLE hSession,
                                    CK_OBJECT_HANDLE hObject,
                                    CK_ATTRIBUTE_PTR pTemplate,
                                    CK_ULONG ulCount)
{
	if (hSession == CK_INVALID_HANDLE)
		return CKR_SESSION_HANDLE_INVALID;

	if (hObject == CK_INVALID_HANDLE)
		return CKR_OBJECT_HANDLE_INVALID;

	if (!pTemplate)
		return CKR_ARGUMENTS_BAD;

	if (!is_lib_initialized())
		return CKR_CRYPTOKI_NOT_INITIALIZED;

        return hal_get_or_set_object_attr(command_id, hSession, hObject, pTemplate, ulCount);
}

/*
 * 11.7 OBJECT MANAGEMENT FUNCTIONS
 */

CK_RV C_CreateObject(CK_SESSION_HANDLE hSession,
		     CK_ATTRIBUTE_PTR pTemplate,
		     CK_ULONG ulCount,
		     CK_OBJECT_HANDLE_PTR phObject)
{
	if (hSession == CK_INVALID_HANDLE)
		return CKR_SESSION_HANDLE_INVALID;

	if (!ulCount || !pTemplate || !phObject)
		return CKR_ARGUMENTS_BAD;

	if (!is_lib_initialized())
		return CKR_CRYPTOKI_NOT_INITIALIZED;

	return hal_create_object(hSession, pTemplate, ulCount, phObject);
}

CK_RV C_CopyObject(CK_SESSION_HANDLE hSession,
		   CK_OBJECT_HANDLE hObject,
		   CK_ATTRIBUTE_PTR pTemplate,
		   CK_ULONG ulCount,
		   CK_OBJECT_HANDLE_PTR phNewObject)
{
	hSession = hSession;
	hObject = hObject;
	pTemplate = pTemplate;
	ulCount = ulCount;
	phNewObject = phNewObject;
	return CKR_FUNCTION_NOT_SUPPORTED;
}

CK_RV C_DestroyObject(CK_SESSION_HANDLE hSession, CK_OBJECT_HANDLE hObject)
{
	if (hSession == CK_INVALID_HANDLE)
		return CKR_SESSION_HANDLE_INVALID;

	if (hObject == CK_INVALID_HANDLE)
		return CKR_OBJECT_HANDLE_INVALID;

	return hal_destroy_object(hSession, hObject);
}

CK_RV C_GetObjectSize(CK_SESSION_HANDLE hSession, CK_OBJECT_HANDLE hObject, CK_ULONG_PTR pulSize)
{
	hSession = hSession;
	hObject = hObject;
	pulSize = pulSize;
	return CKR_FUNCTION_NOT_SUPPORTED;
}

CK_RV C_GetAttributeValue(CK_SESSION_HANDLE hSession,
			  CK_OBJECT_HANDLE hObject,
			  CK_ATTRIBUTE_PTR pTemplate,
			  CK_ULONG ulCount)
{
        return get_or_set_object_attr(TEE_GET_ATTR_VALUE, hSession, hObject, pTemplate, ulCount);
}

CK_RV C_SetAttributeValue(CK_SESSION_HANDLE hSession,
			  CK_OBJECT_HANDLE hObject,
			  CK_ATTRIBUTE_PTR pTemplate,
			  CK_ULONG ulCount)
{
        return get_or_set_object_attr(TEE_SET_ATTR_VALUE, hSession, hObject, pTemplate, ulCount);
}

CK_RV C_FindObjectsInit(CK_SESSION_HANDLE hSession,
			CK_ATTRIBUTE_PTR pTemplate,
			CK_ULONG ulCount)
{
	if (hSession == CK_INVALID_HANDLE)
		return CKR_SESSION_HANDLE_INVALID;

	if (!is_lib_initialized())
		return CKR_CRYPTOKI_NOT_INITIALIZED;

	return hal_find_objects_init(hSession, pTemplate, ulCount);
}

CK_RV C_FindObjects(CK_SESSION_HANDLE hSession,
		    CK_OBJECT_HANDLE_PTR phObject,
		    CK_ULONG ulMaxObjectCount,
		    CK_ULONG_PTR pulObjectCount)
{
	if (hSession == CK_INVALID_HANDLE)
		return CKR_SESSION_HANDLE_INVALID;

	if (!phObject || !pulObjectCount)
		return CKR_ARGUMENTS_BAD;

	if (!is_lib_initialized())
		return CKR_CRYPTOKI_NOT_INITIALIZED;

	return hal_find_objects(hSession, phObject, ulMaxObjectCount, pulObjectCount);
}

CK_RV C_FindObjectsFinal(CK_SESSION_HANDLE hSession)
{
	if (hSession == CK_INVALID_HANDLE)
		return CKR_SESSION_HANDLE_INVALID;

	if (!is_lib_initialized())
		return CKR_CRYPTOKI_NOT_INITIALIZED;

	return hal_find_objects_final(hSession);
}
