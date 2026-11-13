/**
  Copyright (c) 2024-2026, OCR Studio
  All rights reserved.
*/

#ifndef COCRSTUDIOSDK_C_OCR_STUDIO_STRING_H_INCLUDED
#define COCRSTUDIOSDK_C_OCR_STUDIO_STRING_H_INCLUDED

#include <cocrstudiosdk/c_ocr_studio_common.h>

#ifdef __cplusplus
OPEN_EXTERN_C
#endif // __cplusplus

typedef struct {
  char* str_;
  int size_;
} COCRStudioSDKString;

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKStringCreate(
	COCRStudioSDKString* out_string,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKStringDestroy(
	COCRStudioSDKString* string,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKStringCreateFromStr(
	COCRStudioSDKString* out_string,
	const char* str,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKStringCopy(
	COCRStudioSDKString* in_string,
	COCRStudioSDKString* out_string,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKStringAssign(
	COCRStudioSDKString* in_string,
	COCRStudioSDKString* out_string,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKStringAppend(
	COCRStudioSDKString* in_string,
	COCRStudioSDKString* out_string,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKStringConcat(
	COCRStudioSDKString* lhs,
	COCRStudioSDKString* rhs,
	COCRStudioSDKString* out_string,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKStringCStr(
	COCRStudioSDKString* in_string,
	const char** out_str,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKStringSize(
	COCRStudioSDKString* in_string,
	int* out_size,
	COCRStudioSDKErrorMessage* error_message);


#ifdef __cplusplus
CLOSE_EXTERN_C
#endif // __cplusplus

#endif // COCRSTUDIOSDK_C_OCR_STUDIO_STRING_H_INCLUDED
