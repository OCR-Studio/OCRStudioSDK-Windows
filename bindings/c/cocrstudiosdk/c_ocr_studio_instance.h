/**
  Copyright (c) 2024-2026, OCR Studio
  All rights reserved.
*/

#ifndef COCRSTUDIOSDK_C_OCR_STUDIO_INSTANCE_H_INCLUDED
#define COCRSTUDIOSDK_C_OCR_STUDIO_INSTANCE_H_INCLUDED

#include <cocrstudiosdk/c_ocr_studio_common.h>
#include <cocrstudiosdk/c_ocr_studio_session.h>

#ifdef __cplusplus
OPEN_EXTERN_C
#endif // __cplusplus

typedef void* COCRStudioSDKInstance;

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKInstanceCreateStandalone(
	COCRStudioSDKInstance* out_instance,
	const char* json_instance_init_params,
	COCRStudioSDKErrorMessage* error_message);
	
OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKInstanceCreateFromPath(
	COCRStudioSDKInstance* out_instance,
	const char* configuration_filename,
	const char* json_instance_init_params,	// nullptr
	COCRStudioSDKErrorMessage* error_message);
	
OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKInstanceCreateFromBuffer(
	COCRStudioSDKInstance* out_instance,
	unsigned char* configuration_buffer,
  int            configuration_buffer_size,
	const char* json_instance_init_params,	// nullptr
	COCRStudioSDKErrorMessage* error_message);
	
OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKInstanceLibraryVersion(
	const char** out_version,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKInstanceDescription(
	COCRStudioSDKInstance* instance,
	const char** out_description,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKInstanceCreateSession(
	COCRStudioSDKInstance* instance,
	COCRStudioSDKSession* out_session,
	const char* authorization_signature,
	const char* json_session_params,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKInstanceDestroy(
	COCRStudioSDKInstance* instance,
	COCRStudioSDKErrorMessage* error_message);

#ifdef __cplusplus
CLOSE_EXTERN_C
#endif // __cplusplus

#endif // COCRSTUDIOSDK_C_OCR_STUDIO_INSTANCE_H_INCLUDED
