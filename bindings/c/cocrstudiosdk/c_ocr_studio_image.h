/**
  Copyright (c) 2024-2026, OCR Studio
  All rights reserved.
*/

#ifndef COCRSTUDIOSDK_C_OCR_STUDIO_IMAGE_H_INCLUDED
#define COCRSTUDIOSDK_C_OCR_STUDIO_IMAGE_H_INCLUDED

#include <cocrstudiosdk/c_ocr_studio_common.h>
#include <cocrstudiosdk/c_ocr_studio_string.h>

#ifdef __cplusplus
OPEN_EXTERN_C
#endif // __cplusplus

typedef enum {
  COCRStudioSDKPixelFormat_G = 0,     ///< Greyscale
  COCRStudioSDKPixelFormat_GA,        ///< Greyscale + Alpha
  COCRStudioSDKPixelFormat_AG,        ///< Alpha + Greyscale
  COCRStudioSDKPixelFormat_RGB,       ///< RGB
  COCRStudioSDKPixelFormat_BGR,       ///< BGR
  COCRStudioSDKPixelFormat_BGRA,      ///< BGR + Alpha
  COCRStudioSDKPixelFormat_ARGB,      ///< Alpha + RGB
  COCRStudioSDKPixelFormat_RGBA       ///< RGB + Alpha
} COCRStudioSDKPixelFormat;

typedef enum {
  COCRStudioSDKYUVFormat_NOT_SET = 0,  ///< Not set
  COCRStudioSDKYUVFormat_NNV21,        ///< NV 21
  COCRStudioSDKYUVFormat_420_888       ///< YUV 420 888
} COCRStudioSDKYUVFormat;

typedef void* COCRStudioSDKImage;
typedef void* COCRStudioSDKImageRef;

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKImageCreateEmpty(
	COCRStudioSDKImage* out_image,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKImageCreateFromFile(
	COCRStudioSDKImage* out_image,
	const char*	filename,
	int		page_number, 	// 0
	int 	max_width,		// 25000
	int 	max_height,		// 25000
	COCRStudioSDKErrorMessage* error_message);
	
OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKImageCreateFromFileBuffer(
	COCRStudioSDKImage* out_image,
	unsigned char*	data,
	int 	data_size, 
	int		page_number,	// 0
	int 	max_width,		// 25000
	int 	max_height,		// 25000
	COCRStudioSDKErrorMessage* error_message);
	
OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKImageCreateFromBase64FileBuffer(
	COCRStudioSDKImage* out_image,
	const char*	base64_data,
	int		page_number,	// 0
	int 	max_width,		// 25000
	int 	max_height,		// 25000
	COCRStudioSDKErrorMessage* error_message);
	
OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKImageCreateFromPixelBuffer(
	COCRStudioSDKImage* out_image,
	unsigned char*	data,
	int		data_size, 
	int		width,
	int		height,
	int		bytes_per_line,
	int 		bytes_per_channel,
	COCRStudioSDKPixelFormat	pixel_format,
	COCRStudioSDKErrorMessage* error_message);
	
OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKImageCreateFromBuffer(
	COCRStudioSDKImage* out_image,
	unsigned char*	data,
	int		data_size, 
	int		width,
	int		height,
	int		bytes_per_line,
	int 	channels,
	COCRStudioSDKErrorMessage* error_message);
	
OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKImageCreateFromYUVSimple(
	COCRStudioSDKImage* out_image,
	unsigned char*	yuv_data,
	int		yuv_data_size, 
	int		width,
	int		height,
	COCRStudioSDKErrorMessage* error_message);
	
OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKImageCreateFromYUV(
	COCRStudioSDKImage* out_image,
	unsigned char* y_plane,
  int            y_plane_size,
  int            y_plane_row_stride,
  int            y_plane_pixel_stride,
  unsigned char* u_plane,
  int            u_plane_size,
  int            u_plane_row_stride,
  int            u_plane_pixel_stride,
  unsigned char* v_plane,
  int            v_plane_size,
  int            v_plane_row_stride,
  int            v_plane_pixel_stride,
  int            width,
  int            height,
  COCRStudioSDKYUVFormat yuv_format,
  COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKImageGetRef(
  COCRStudioSDKImage* in_image,
  COCRStudioSDKImageRef* out_image,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKImageDestroy(
	COCRStudioSDKImage* in_image,
	COCRStudioSDKErrorMessage* error_message);
      	
OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKImagePagesCount(
	const char* filename, 
	int* out_pages_count,
	COCRStudioSDKErrorMessage* error_message);
	
OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKImagePageName(
	const char* filename, 
	int page_number,
	COCRStudioSDKString* out_page_name,
	COCRStudioSDKErrorMessage* error_message);
      	
OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKImageDeepCopy(
	COCRStudioSDKImageRef in_image,
	COCRStudioSDKImage* out_image,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKImageShallowCopy(
	COCRStudioSDKImageRef in_image,
	COCRStudioSDKImage* out_image,
	COCRStudioSDKErrorMessage* error_message);
	
OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKImageClear(
	COCRStudioSDKImage* in_image,
	COCRStudioSDKErrorMessage* error_message);
	
OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKImageExportPixelBufferLength(
	COCRStudioSDKImageRef in_image,
	int* out_length,
	COCRStudioSDKErrorMessage* error_message);
	
OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKImageExportPixelBuffer(
	COCRStudioSDKImageRef in_image,
	unsigned char* export_buffer, 
	int export_buffer_length,
	int* out_bytes,
	COCRStudioSDKErrorMessage* error_message);
	
OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKImageExportBase64JPEG(
	COCRStudioSDKImageRef in_image,
	COCRStudioSDKString* out,
	COCRStudioSDKErrorMessage* error_message);
	
OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKImageScale(
	COCRStudioSDKImageRef in_image,
	int width, 
	int height,
	COCRStudioSDKErrorMessage* error_message);
	
OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKImageDeepCopyScaled(
	COCRStudioSDKImageRef in_image,
	COCRStudioSDKImage* out_image,
	int width,
	int height,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKImageCropByQuad(
	COCRStudioSDKImageRef image,
	const char* quad_json, 
	int width, 
	int height,
	COCRStudioSDKErrorMessage* error_message);
	
OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKImageDeepCopyCroppedByQuad(
	COCRStudioSDKImageRef in_image,
	COCRStudioSDKImage* out_image,
	const char* quad_json, 
	int width, 
	int height,
	COCRStudioSDKErrorMessage* error_message);
	
OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKImageCropByRect(
	COCRStudioSDKImageRef in_image,
	int x, 
	int y, 
	int width, 
	int height,
	COCRStudioSDKErrorMessage* error_message);
	
OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKImageDeepCopyCroppedByRect(
	COCRStudioSDKImageRef in_image,
	COCRStudioSDKImage* out_image,
	int x, 
	int y, 
	int width, 
	int height,
	COCRStudioSDKErrorMessage* error_message);
	
OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKImageShallowCopyCroppedByRect(
	COCRStudioSDKImageRef in_image,
	COCRStudioSDKImage* out_image,
	int x, 
	int y, 
	int width, 
	int height,
	COCRStudioSDKErrorMessage* error_message);
	
OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKImageRotateByNinety(
	COCRStudioSDKImageRef in_image,
	int num_rotations,
	COCRStudioSDKErrorMessage* error_message);
	
OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKImageDeepCopyRotatedByNinety(
	COCRStudioSDKImageRef in_image,
	COCRStudioSDKImage* out_image,
	int num_rotations,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKImageWidth(
	COCRStudioSDKImageRef in_image,
	int* out_width,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKImageHeight(
	COCRStudioSDKImageRef in_image,
	int* out_height,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKImageBytesPerLine(
	COCRStudioSDKImageRef in_image,
	int* out_bytesPerLine,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKImageChannels(
	COCRStudioSDKImageRef in_image,
	int* out_channels,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKImageOwnsPixelData(
	COCRStudioSDKImageRef in_image,
	int* out_ownsPixelData,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKImageForcePixelDataOwnership(
	COCRStudioSDKImageRef in_image,
	COCRStudioSDKErrorMessage* error_message);

#ifdef __cplusplus
CLOSE_EXTERN_C
#endif // __cplusplus


#endif // COCRSTUDIOSDK_C_OCR_STUDIO_IMAGE_H_INCLUDED
