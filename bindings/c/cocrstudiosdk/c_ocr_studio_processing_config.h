/**
  Copyright (c) 2024-2026, OCR Studio
  All rights reserved.
*/

#ifndef COCRSTUDIOSDK_C_OCR_STUDIO_PROCESSING_CONFIG_H_INCLUDED
#define COCRSTUDIOSDK_C_OCR_STUDIO_PROCESSING_CONFIG_H_INCLUDED

#include <cocrstudiosdk/c_ocr_studio_common.h>

#ifdef __cplusplus
OPEN_EXTERN_C
#endif // __cplusplus

// 
typedef void* COCRStudioSDKProcessingConfig;
typedef void* COCRStudioSDKProcessingConfigRef;

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKProcessingConfigCreate(
	COCRStudioSDKProcessingConfig* out_config,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKProcessingConfigDestroy(
	COCRStudioSDKProcessingConfig* config,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKProcessingConfigCreateFromJSON(
	COCRStudioSDKProcessingConfig* out_config,
	const char* json_path,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKProcessingConfigCreateFromBuffer(
	COCRStudioSDKProcessingConfig* out_config,
	const unsigned char* data,
	unsigned long size,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKProcessingConfigGetRef(
	COCRStudioSDKProcessingConfig* in_config,
	COCRStudioSDKProcessingConfigRef* out_config,
	COCRStudioSDKErrorMessage* error_message);

#ifdef __cplusplus
CLOSE_EXTERN_C
#endif // __cplusplus

#endif // COCRSTUDIOSDK_C_OCR_STUDIO_PROCESSING_CONFIG_H_INCLUDED
