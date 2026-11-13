/**
  Copyright (c) 2024-2026, OCR Studio
  All rights reserved.
*/

#ifndef COCRSTUDIOSDK_C_OCR_STUDIO_COMMON_H_INCLUDED
#define COCRSTUDIOSDK_C_OCR_STUDIO_COMMON_H_INCLUDED

#define OPEN_EXTERN_C extern "C" {
#define CLOSE_EXTERN_C }

#ifdef __cplusplus
OPEN_EXTERN_C
#endif // __cplusplus

#if defined _WIN32 && OCRSTUDIO_ENGINE_EXPORTS
# define OCR_STUDIO_SDK_DLL_EXPORT __declspec(dllexport)
#else
# if defined(__clang__) || defined(__GNUC__)
#  define OCR_STUDIO_SDK_DLL_EXPORT __attribute__ ((visibility ("default")))
# else
#  define OCR_STUDIO_SDK_DLL_EXPORT
# endif
#endif

typedef struct {
  char* buffer;
  unsigned int buffer_size;
} COCRStudioSDKErrorMessage;


#ifdef __cplusplus
CLOSE_EXTERN_C
#endif // __cplusplus

#endif // COCRSTUDIOSDK_C_OCR_STUDIO_COMMON_H_INCLUDED
