/**
  Copyright (c) 2024-2026, OCR Studio
  All rights reserved.
*/

#ifndef COCRSTUDIOSDK_C_OCR_STUDIO_RESULT_H_INCLUDED
#define COCRSTUDIOSDK_C_OCR_STUDIO_RESULT_H_INCLUDED

#include <cocrstudiosdk/c_ocr_studio_common.h>
#include <cocrstudiosdk/c_ocr_studio_image.h>
#include <cocrstudiosdk/c_ocr_studio_string.h>

#ifdef __cplusplus
OPEN_EXTERN_C
#endif // __cplusplus

// mixed owned
typedef void* COCRStudioSDKItem;
typedef void* COCRStudioSDKItemRef;

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKItemType(
	COCRStudioSDKItemRef in_item,
	const char** out_type,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKItemName(
	COCRStudioSDKItemRef in_item,
	const char** out_name,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKItemValue(
	COCRStudioSDKItemRef in_item,
	const char** out_value,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKItemConfidence(
	COCRStudioSDKItemRef in_item,
	double* out_confidence,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKItemAccepted(
	COCRStudioSDKItemRef in_item,
	int* out_accepted,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKItemAttributes(
	COCRStudioSDKItemRef in_item,
	const char** out_attributes,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKItemHasImage(
	COCRStudioSDKItemRef in_item,
	int* out_hasImage,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKItemDescription(
	COCRStudioSDKItemRef in_item,
	const char** out_description,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKItemImage(
	COCRStudioSDKItemRef ref_item,
	COCRStudioSDKImageRef* out_image,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKItemGetRef(
  COCRStudioSDKItem* in_item,
  COCRStudioSDKItemRef* out_item,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKItemDestroy(
  COCRStudioSDKItem* item,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKItemDeepCopy(
  COCRStudioSDKItemRef in_item,
	COCRStudioSDKItem* out_item,
	COCRStudioSDKErrorMessage* error_message);

// client-owned
typedef void* COCRStudioSDKItemIterator;

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKItemIteratorDestroy(
	COCRStudioSDKItemIterator* iter,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKItemIteratorIsEqual(
	COCRStudioSDKItemIterator lhs,
	COCRStudioSDKItemIterator rhs,
	int* out_equal,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKItemIteratorNext(
	COCRStudioSDKItemIterator in_iter,
	COCRStudioSDKItemIterator* out_iter,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKItemIteratorStep(
	COCRStudioSDKItemIterator out_iter,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKItemIteratorKey(
	COCRStudioSDKItemIterator in_iter,
	const char** out_key,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKItemIteratorItem(
	COCRStudioSDKItemIterator in_iter,
	COCRStudioSDKItemRef* out_item,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKItemIteratorCopy(
  COCRStudioSDKItemIterator in_iter,
  COCRStudioSDKItemIterator* out_iter,
  COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKItemIteratorAssign(
  COCRStudioSDKItemIterator lhs,
  COCRStudioSDKItemIterator rhs,
  COCRStudioSDKErrorMessage* error_message);

// library-owned
typedef void* COCRStudioSDKTargetRef;

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKTargetDescription(
	COCRStudioSDKTargetRef target,
	const char** out_description,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKTargetItemsCountByType(
	COCRStudioSDKTargetRef target,
	const char* type,
	int* out_count,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKTargetHasItem(
	COCRStudioSDKTargetRef target,
	const char* type,
	const char* name,
	int* out_hasItem,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKTargetItem(
	COCRStudioSDKTargetRef target,
	const char* type,
	const char* name,
	COCRStudioSDKItemRef* out_item,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKTargetItemsBegin(
	COCRStudioSDKTargetRef target,
	COCRStudioSDKItemIterator* out_it,
	const char* type,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKTargetItemsEnd(
	COCRStudioSDKTargetRef target,
	COCRStudioSDKItemIterator* out_it,
	const char* type,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKTargetIsFinal(
	COCRStudioSDKTargetRef target,
	int* out_isFinal,
	COCRStudioSDKErrorMessage* error_message);

// mixed-owned
typedef void* COCRStudioSDKResult;
typedef void* COCRStudioSDKResultRef;

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKResultDeepCopy(
	COCRStudioSDKResultRef in_result,
	COCRStudioSDKResult* out_result,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKResultDestroy(
	COCRStudioSDKResult* result,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKResultGetRef(
  COCRStudioSDKResult* in_result,
  COCRStudioSDKResultRef* out_result,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKResultTargetsCount(
	COCRStudioSDKResultRef in_result,
	int* out_count,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKResultTargetByIndex(
	COCRStudioSDKTargetRef in_result,
	int idx,
	COCRStudioSDKResultRef* out_result,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKResultAllTargetsFinal(
	COCRStudioSDKResultRef result,
	int* out_final,
	COCRStudioSDKErrorMessage* error_message);

OCR_STUDIO_SDK_DLL_EXPORT int COCRStudioSDKResultSerialize(
	COCRStudioSDKResultRef in_result,
	COCRStudioSDKString* out_result,
	COCRStudioSDKErrorMessage* error_message);

#ifdef __cplusplus
CLOSE_EXTERN_C
#endif // __cplusplus

#endif // COCRSTUDIOSDK_C_OCR_STUDIO_RESULT_H_INCLUDED
