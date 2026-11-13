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
  COCRStudioSDKImage image = NULL;

  int ret = 0;

  do {
    // 1st argument - path to the image to be recognized
    // 2nd argument - path to the configuration config
    // 3rd argument - target mask
    const char* lib_version = NULL;
    if (COCRStudioSDKInstanceLibraryVersion(&lib_version, &error_message) != 0) {
      return report_error(error_message.buffer);
    }
    if (argc != 4) {
      printf("Version %s. Usage: "
             "%s <image_path> <config_path> <target_mask>\n",
          lib_version, argv[0]);
      ret = -1;
      break;
    }

    const char* image_path = argv[1];
    const char* config_path = argv[2];
    const char* target_mask = argv[3];

    printf("OCRStudioSDK version %s\n", lib_version);
    printf("image_path = %s\n", image_path);
    printf("config_path = %s\n", config_path);
    printf("target_mask = %s\n", target_mask);
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
      "\"session_type\": \"document_recognition\", "
      "\"target_group_type\": \"default\", "
      "\"target_masks\": \"%s\", "
      "\"output_modes\": ["
      "\"character_alternatives\", "
      "\"field_geometry\" "
      "] "
      "}",
      target_mask);
   
    // Creating a session object - a main handle for performing recognition.
    // Note you should put your SDK signature verification as the first parameter.
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

    // Creating an image object which will be used as an input for the session.
    if (COCRStudioSDKImageCreateFromFile(
       &image, image_path, 0, 25000, 25000, &error_message) != 0) {
      ret = report_error(error_message.buffer);
      break;
    }
    
    // Performing the recognition.
    if (COCRStudioSDKSessionProcessImage(session, image, &error_message) != 0) {
      ret = report_error(error_message.buffer);
      break;
    }

    // Obtaining the recognition result.
    COCRStudioSDKResultRef result_ref = NULL;
    if (COCRStudioSDKSessionCurrentResult(session, &result_ref, &error_message) != 0) {
      ret = report_error(error_message.buffer);
      break;
    }

    // Printing the contents of the recognition result.
    int targets_count = 0;
    if (COCRStudioSDKResultTargetsCount(result_ref, &targets_count, &error_message) != 0) {
      ret = report_error(error_message.buffer);
      break;
    }
    printf("Targets count: %d\n", targets_count);
    for (int i = 0; i < targets_count; ++i) {
      COCRStudioSDKTargetRef target_ref = NULL;
      if (COCRStudioSDKResultTargetByIndex(result_ref, i, &target_ref, &error_message) != 0) {
        ret = report_error(error_message.buffer);
        break;
      }
      const char* target_description = NULL;
      if (COCRStudioSDKTargetDescription(target_ref, &target_description, &error_message) != 0) {
        ret = report_error(error_message.buffer);
        break;
      }
      printf("Target %d description:\n%s\n\n", i, target_description);
      int items_count_by_type;
      if (COCRStudioSDKTargetItemsCountByType(target_ref, "string", &items_count_by_type, &error_message) != 0) {
        ret = report_error(error_message.buffer);
        break;
      }
      printf("Number of strings: %d\n", items_count_by_type);
      printf("Strings:\n");
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

        const char* item_description = NULL;
        if (COCRStudioSDKItemDescription(item_ref, &item_description, &error_message) != 0) {
          ret = report_error(error_message.buffer);
          break;
        }

        printf("  %s: %s\n\n", item_name, item_description);

        if (COCRStudioSDKItemIteratorStep(it_begin, &error_message) != 0) {
          ret = report_error(error_message.buffer);
          break;
        }
      }
      COCRStudioSDKItemIteratorDestroy(&it_begin, &error_message);
      COCRStudioSDKItemIteratorDestroy(&it_end, &error_message);

      int is_final = 0;
      if (COCRStudioSDKTargetIsFinal(target_ref, &is_final, &error_message) != 0) {
        ret = report_error(error_message.buffer);
        break;
      }
      printf("Is target final: %s\n\n", (is_final == 1 ? "true" : "false"));
    }
    int all_final = 0;
    if (COCRStudioSDKResultAllTargetsFinal(result_ref, &all_final, &error_message) != 0) {
      ret = report_error(error_message.buffer);
      break;
    }
    printf("Is result final: %s", (all_final == 1 ? "true" : "false"));
  } while (0);


  if (image) {
    COCRStudioSDKImageDestroy(&image, &error_message);
  }
  if (session) {
    COCRStudioSDKSessionDestroy(&session, &error_message);
  }
  if (engine_instance) {
    COCRStudioSDKInstanceDestroy(&engine_instance, &error_message);
  }

  return ret;
}
