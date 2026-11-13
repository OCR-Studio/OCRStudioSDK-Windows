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
#include <ocrstudiosdk/ocr_studio_delegate.h>

// Implementing optional feedback reporter - in this way you can set up
//     callbacks for receiving the information before frame is processed
// This is not needed unless you wish to visualize some feedback info
//     during the recognition process.
class OptionalDelegate : public ocrstudio::OCRStudioSDKDelegate {
 public:
  virtual ~OptionalDelegate() override = default;

  public:
    virtual void Callback(const char* json_message) override {
     printf("[Feedback called]:\n%s\n", json_message);
    }
};

int main(int argc, char **argv) {

  // 1st argument - path to the image to be recognized
  // 2nd argument - path to the configuration config
  // 3rd argument - target mask
  if (argc != 4) {
    printf("Version %s. Usage: "
           "%s <image_path> <config_path> <target_mask>\n",
        ocrstudio::OCRStudioSDKInstance::LibraryVersion(), argv[0]);
    return -1;
  }

  const std::string image_path = argv[1];
  const std::string config_path = argv[2];
  const std::string target_mask = argv[3];

  printf("OCRStudioSDK version %s\n",
         ocrstudio::OCRStudioSDKInstance::LibraryVersion());
  printf("image_path = %s\n", image_path.c_str());
  printf("config_path = %s\n", config_path.c_str());
  printf("target_mask = %s\n", target_mask.c_str());
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
    session_params += "\"session_type\": \"document_recognition\", ";
    session_params += "\"target_group_type\": \"default\", ";
    session_params += "\"target_masks\": \"" + target_mask + "\", ";
    session_params += "\"output_modes\": [";
    session_params += "\"character_alternatives\", ";
    session_params += "\"field_geometry\" ";
    session_params += "], ";
    session_params += "\"options\":{";

    // Fraud attempt detection enabling.
    // Note: Fraud attempt detection must be included in your package.
    // session_params += "\"fraudAttemptEnabled\": \"true\" ";

    session_params += "}";
    session_params += "}";

    OptionalDelegate optional_delegate;
   
    // Creating a session object - a main handle for performing recognition.
    // Note you should put your SDK signature verification as the first parameter.
    std::unique_ptr<ocrstudio::OCRStudioSDKSession> session(
        engine_instance->CreateSession({put_your_personalized_signature_from_doc_README.md}, session_params.c_str(), &optional_delegate));

    // Printing Description of the created session object.
    printf("Session description:\n");
    printf("%s\n", session->Description());
    printf("\n");

    // Creating an image object which will be used as an input for the session.
    std::unique_ptr<ocrstudio::OCRStudioSDKImage> image(
        ocrstudio::OCRStudioSDKImage::CreateFromFile(image_path.c_str()));
    
    
    // Performing the recognition.
    session->ProcessImage(*image);

    // Obtaining the recognition result.
    const ocrstudio::OCRStudioSDKResult& result = session->CurrentResult();

    // Printing the contents of the recognition result.
    printf("Targets count: %d\n", result.TargetsCount());
    for (int i = 0; i < result.TargetsCount(); ++i) {
      const ocrstudio::OCRStudioSDKTarget& target = result.TargetByIndex(i);
      printf("Target %d description:\n", i);
      printf("%s\n", target.Description());
      printf("\n");

      //Printing string items.
      printf("Number of strings: %d\n", target.ItemsCountByType("string"));
      printf("Strings:\n");
      for (auto it = target.ItemsBegin("string"); it != target.ItemsEnd("string"); it.Step()) {
        printf("  %s: %s\n\n", it.Item().Name(), it.Item().Description());
      }

      //Printing fraud_attempt items if there are any.
      if (target.ItemsCountByType("fraud_attempt") > 0) {
        printf("Number of fraud attempts: %d\n", target.ItemsCountByType("fraud_attempt"));
        printf("Fraud attempts:\n");
        for (auto it = target.ItemsBegin("fraud_attempt"); it != target.ItemsEnd("fraud_attempt"); it.Step()) {
          printf("  %s: %s\n\n", it.Item().Name(), it.Item().Description());
        }
      }

      printf("Is target final: %s\n\n",
             (target.IsFinal() ? "true" : "false"));
    }
    printf("Is result final: %s",
           (result.AllTargetsFinal() ? "true" : "false"));

  } catch (const ocrstudio::OCRStudioSDKException& e) {
    printf("Exception thrown: %s\n", e.Message());
    return -1;
  }

  return 0;
}
