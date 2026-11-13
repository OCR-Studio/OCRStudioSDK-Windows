/**
  Copyright (c) 2024-2026, OCR Studio
  All rights reserved.
*/

#ifndef COCRSTUDIOSDK_C_OCR_STUDIO_SESSION_H_INCLUDED
#define COCRSTUDIOSDK_C_OCR_STUDIO_SESSION_H_INCLUDED

#include <cocrstudiosdk/c_ocr_studio_common.h>
#include <cocrstudiosdk/c_ocr_studio_image.h>
#include <cocrstudiosdk/c_ocr_studio_result.h>
#include <cocrstudiosdk/c_ocr_studio_processing_config.h>

#ifdef __cplusplus
OPEN_EXTERN_C
#endif // __cplusplus

// library owned
typedef void* COCRStudioSDKSession;

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKSessionDescription(
	COCRStudioSDKSession session,
	const char** out_description,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKSessionProcessImage(
	COCRStudioSDKSession session,
	COCRStudioSDKImageRef ref_image,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKSessionProcessData(
	COCRStudioSDKSession session,
	const char* data_str,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKSessionCurrentResult(
	COCRStudioSDKSession session,
	COCRStudioSDKResultRef* out_result,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKSessionReset(
	COCRStudioSDKSession session,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKSessionSuspend(
	COCRStudioSDKSession session,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKSessionResume(
	COCRStudioSDKSession session,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKSessionRegisterConfig(
	COCRStudioSDKSession session,
	COCRStudioSDKProcessingConfigRef config,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKSessionDestroy(
	COCRStudioSDKSession* session,
	COCRStudioSDKErrorMessage* error_message);

#ifdef __cplusplus
CLOSE_EXTERN_C
#endif // __cplusplus

#endif // COCRSTUDIOSDK_C_OCR_STUDIO_SESSION_H_INCLUDED
