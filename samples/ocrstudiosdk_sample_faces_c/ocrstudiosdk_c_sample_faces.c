/**
  Copyright (c) 2024-2026, OCR Studio
  All rights reserved.
*/

#include <stdio.h>

#include <cocrstudiosdk/c_ocr_studio_instance.h>
#include <cocrstudiosdk/c_ocr_studio_result.h>

static int report_error(const char* msg) {
  fflush(stdout);
  fprintf(stderr, "[Error]: %s\n", msg);
  return 1;
}

int main(int argc, char **argv) {
  char error_buf[1024];
  COCRStudioSDKErrorMessage error_message = { error_buf, sizeof(error_buf) };
  
  COCRStudioSDKInstance engine_instance = NULL;
  COCRStudioSDKSession session = NULL;
  COCRStudioSDKImage image_lvalue = NULL;
  COCRStudioSDKImage image_rvalue = NULL;

  int ret = 0;

  do {
  // 1st argument - path to the first image for face comparison
  // 2nd argument - path to the second image for face comparison
  // 3rd argument - path to configuration config
    const char* lib_version = NULL;
    if (COCRStudioSDKInstanceLibraryVersion(&lib_version, &error_message) != 0) {
      return report_error(error_message.buffer);
    }
    if (argc != 4) {
      printf("Version %s. Usage: %s <image_path_lvalue> <image_path_rvalue> "
           "<config_path>\n", lib_version, argv[0]);
      ret = -1;
      break;
    }

    const char* image_path_lvalue = argv[1];
    const char* image_path_rvalue = argv[2];
    const char* config_path = argv[3];

    printf("OCRStudioSDK version %s\n", lib_version);
    printf("image_path_lvalue = %s\n", image_path_lvalue);
    printf("image_path_rvalue = %s\n", image_path_rvalue);
    printf("config_path = %s\n", config_path);
    printf("\n");

    // Creating the recognition engine object - initializes all internal
    //     configuration structure. Second parameter to the factory method
    //     is the optional JSON with initialization parameters (see documentation).
    if (COCRStudioSDKInstanceCreateFromPath(&engine_instance, config_path, NULL, &error_message) != 0) {
      ret = report_error(error_message.buffer);
      break;
    }

    // Printing Description of the created engine object.
    const char* instance_description = NULL;
    if (COCRStudioSDKInstanceDescription(&engine_instance, &instance_description, &error_message) != 0) {
      ret = report_error(error_message.buffer);
      break;
    }
    printf("Engine instance description:\n%s\n\n", instance_description);

    // Parameters necessary for session creation.
    char session_params[1024];
    snprintf(session_params, sizeof(session_params),
      "{"
      "\"session_type\": \"face_matching\", "
      "\"target_group_type\": \"default\""
      "}");
   
    // Creating a session object - a main handle for performing
    //     face matching. Note you should put your SDK signature 
    //     verification as the first parameter.
    if (COCRStudioSDKInstanceCreateSession(
      &engine_instance, &session, {put_your_personalized_signature_from_doc_README.md}, session_params, &error_message) != 0) {
      ret = report_error(error_message.buffer);
      break;
    }

    // Printing Description of the created session object.
    const char* session_description = NULL;
    if (COCRStudioSDKSessionDescription(session, &session_description, &error_message) != 0) {
      ret = report_error(error_message.buffer);
      break;
    }
    printf("Session description:\n%s\n\n", session_description);

    // Creating image objects which will be used for face matching.
    if (COCRStudioSDKImageCreateFromFile(
       &image_lvalue, image_path_lvalue, 0, 25000, 25000, &error_message) != 0) {
      ret = report_error(error_message.buffer);
      break;
    }
    if (COCRStudioSDKImageCreateFromFile(
       &image_rvalue, image_path_rvalue, 0, 25000, 25000, &error_message) != 0) {
      ret = report_error(error_message.buffer);
      break;
    }
    
    // Performing face matching between two images.
    if (COCRStudioSDKSessionProcessImage(session, image_lvalue, &error_message) != 0) {
      ret = report_error(error_message.buffer);
      break;
    }
    if (COCRStudioSDKSessionProcessImage(session, image_rvalue, &error_message) != 0) {
      ret = report_error(error_message.buffer);
      break;
    }

    // Obtaining the face matching result.
    COCRStudioSDKResultRef result_ref = NULL;
    if (COCRStudioSDKSessionCurrentResult(session, &result_ref, &error_message) != 0) {
      ret = report_error(error_message.buffer);
      break;
    }

    // Printing the contents of the face matching result.
    COCRStudioSDKTargetRef target_ref = NULL;
    if (COCRStudioSDKResultTargetByIndex(result_ref, 0, &target_ref, &error_message) != 0) {
      ret = report_error(error_message.buffer);
      break;
    }
    const char* target_description = NULL;
    if (COCRStudioSDKTargetDescription(target_ref, &target_description, &error_message) != 0) {
      ret = report_error(error_message.buffer);
      break;
    }
    printf("Target description:\n%s\n\n", target_description);

    printf("Items:\n");
    COCRStudioSDKItemIterator it_begin = NULL;
    COCRStudioSDKItemIterator it_end = NULL;
    if (COCRStudioSDKTargetItemsBegin(target_ref, &it_begin, "string", &error_message) != 0 ||
        COCRStudioSDKTargetItemsEnd(target_ref, &it_end, "string", &error_message) != 0) {
      ret = report_error(error_message.buffer);
      break;
    }

    // iteration
    for (;;) {
      int is_equal = 0;
      if (COCRStudioSDKItemIteratorIsEqual(it_begin, it_end, &is_equal, &error_message) != 0) {
        ret = report_error(error_message.buffer);
        break;
      }
      // check iteration end
      if (is_equal == 1) {
        break;
      }

      COCRStudioSDKItemRef item_ref = NULL;
      if (COCRStudioSDKItemIteratorItem(it_begin, &item_ref, &error_message) != 0) {
        ret = report_error(error_message.buffer);
        break;
      }

      const char* item_name = NULL;
      if (COCRStudioSDKItemName(item_ref, &item_name, &error_message) != 0) {
        ret = report_error(error_message.buffer);
        break;
      }

      const char* item_value = NULL;
      if (COCRStudioSDKItemValue(item_ref, &item_value, &error_message) != 0) {
        ret = report_error(error_message.buffer);
        break;
      }

      printf("  %s: %s\n", item_name, item_value);

      if (COCRStudioSDKItemIteratorStep(it_begin, &error_message) != 0) {
        ret = report_error(error_message.buffer);
        break;
      }
    }
    COCRStudioSDKItemIteratorDestroy(&it_begin, &error_message);
    COCRStudioSDKItemIteratorDestroy(&it_end, &error_message);

  } while (0);


  if (image_lvalue) {
    COCRStudioSDKImageDestroy(&image_lvalue, &error_message);
  }
  if (image_rvalue) {
    COCRStudioSDKImageDestroy(&image_rvalue, &error_message);
  }
  if (session) {
    COCRStudioSDKSessionDestroy(&session, &error_message);
  }
  if (engine_instance) {
    COCRStudioSDKInstanceDestroy(&engine_instance, &error_message);
  }

  return ret;
}
