/**
  Copyright (c) 2024-2026, OCR Studio
  All rights reserved.
*/

#include <cstring>
#include <string>
#include <memory>
#include <cstdio>

#include <ocrstudiosdk/ocr_studio_instance.h>
#include <ocrstudiosdk/ocr_studio_exception.h>
#include <ocrstudiosdk/ocr_studio_result.h>

int main(int argc, char **argv) {

  // 1st argument - path to the first image for face comparison
  // 2nd argument - path to the second image for face comparison
  // 3rd argument - path to configuration config
  if (argc != 4) {
    printf("Version %s. Usage: %s <image_path_lvalue> <image_path_rvalue> "
           "<config_path>\n",
        ocrstudio::OCRStudioSDKInstance::LibraryVersion(), argv[0]);
    return -1;
  }

  const std::string image_path_lvalue = argv[1];
  const std::string image_path_rvalue = argv[2];
  const std::string config_path = argv[3];

  printf("OCRStudioSDK version %s\n",
         ocrstudio::OCRStudioSDKInstance::LibraryVersion());
  printf("image_path_lvalue = %s\n", image_path_lvalue.c_str());
  printf("image_path_rvalue = %s\n", image_path_rvalue.c_str());
  printf("config_path = %s\n", config_path.c_str());
  printf("\n");

  try {
    // Creating the recognition engine object - initializes all internal
    //     configuration structure. Second parameter to the factory method
    //     is the optional JSON with initialization parameters (see documentation).
    std::unique_ptr<ocrstudio::OCRStudioSDKInstance> engine_instance(
        ocrstudio::OCRStudioSDKInstance::CreateFromPath(config_path.c_str()));

    // Printing Description of the created engine object.
    printf("Engine instance description:\n");
    printf("%s\n", engine_instance->Description());
    printf("\n");

    // Parameters necessary for session creation.
    std::string session_params = "{";
    session_params += "\"session_type\": \"face_matching\", ";
    session_params += "\"target_group_type\": \"default\"";
    session_params += "}";
   
    // Creating a session object - a main handle for performing
    //     face matching. Note you should put your SDK signature 
    //     verification as the first parameter.
    std::unique_ptr<ocrstudio::OCRStudioSDKSession> session(
        engine_instance->CreateSession({put_your_personalized_signature_from_doc_README.md}, session_params.c_str()));

    // Printing Description of the created session object.
    printf("Session description:\n");
    printf("%s\n", session->Description());
    printf("\n");

    // Creating image objects which will be used for face matching.
    std::unique_ptr<ocrstudio::OCRStudioSDKImage> image_lvalue(
        ocrstudio::OCRStudioSDKImage::CreateFromFile(image_path_lvalue.c_str()));
    std::unique_ptr<ocrstudio::OCRStudioSDKImage> image_rvalue(
        ocrstudio::OCRStudioSDKImage::CreateFromFile(image_path_rvalue.c_str()));

    // Performing face matching between two images.
    session->ProcessImage(*image_lvalue);
    session->ProcessImage(*image_rvalue);

    // Obtaining the face matching result.
    const ocrstudio::OCRStudioSDKResult& result = session->CurrentResult();
    
    // Printing the contents of the face matching result.
    const ocrstudio::OCRStudioSDKTarget& target = result.TargetByIndex(0);
    printf("Target description:\n");
    printf("%s\n", target.Description());
    printf("\n");
    printf("Items:\n");
    for (auto it = target.ItemsBegin("string"); it != target.ItemsEnd("string"); it.Step()) {
      printf("  %s: %s\n", it.Item().Name(), it.Item().Value());
    }

  } catch (const ocrstudio::OCRStudioSDKException& e) {
    printf("Exception thrown: %s\n", e.Message());
    return -1;
  }

  return 0;
}
