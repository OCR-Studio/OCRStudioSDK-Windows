/**
  Copyright (c) 2024-2026, OCR Studio
  All rights reserved.
*/

import java.util.Objects;

import ai.ocrstudio.sdk.*;

public class Main {

  static {
    System.loadLibrary("jniocrstudiosdk");
  }

  public static class OptionalDelegate extends OCRStudioSDKDelegate {
    public void Callback(String json_message) {
      System.out.printf("[Feedback called]:\n%s\n", json_message);
    }
  }

  public static OptionalDelegate optional_delegate = new OptionalDelegate();

  public static void main(String[] args) {

    // 1st argument - path to the image to be recognized
    // 2nd argument - path to the configuration config
    // 3rd argument - target mask, "*" by default
    if (args.length != 2 && args.length != 3) {
      System.out.printf("Version %s. Usage: ocrstudiosdk_sample_java " + 
          " <image_path> <config_path> <target_mask>\n", 
          OCRStudioSDKInstance.LibraryVersion());
      System.exit(-1);
    }

    String image_path = args[0];
    String config_path = args[1];
    String target_mask = args.length >= 3 ? args[2] : "*";

    System.out.printf("OCRStudioSDK version %s\n", 
                      OCRStudioSDKInstance.LibraryVersion());
    System.out.printf("image_path = %s\n", image_path);
    System.out.printf("config_path = %s\n", config_path);
    System.out.printf("target_mask = %s\n", target_mask);
    System.out.println();
    System.out.flush();

    try {
      // Creating the recognition engine object - initializes all internal
      //     configuration structure. Second parameter to the factory method
      //     is the optional JSON with initialization parameters (see documentation).
      OCRStudioSDKInstance engine_instance = OCRStudioSDKInstance.CreateFromPath(config_path);

      // Printing Description of the created engine object.
      System.out.printf("Engine instance description:\n");
      System.out.printf("%s\n", engine_instance.Description());
      System.out.println();
      System.out.flush();

      // Parameters necessary for session creation.
      String session_params = "{";
      session_params += "\"session_type\": \"document_recognition\", ";
      session_params += "\"target_group_type\": \"default\", ";
      session_params += "\"target_masks\": \"" + target_mask + "\", ";
      session_params += "\"output_modes\": [";
      session_params += "\"character_alternatives\", ";
      session_params += "\"field_geometry\" ";
      session_params += "] ";
      session_params += "}";

      // Creating a session object - a main handle for performing recognition.
      // Note you should put your SDK signature verification as the first parameter.
      OCRStudioSDKSession session = engine_instance.CreateSession({put_your_personalized_signature_from_doc_README.md}, session_params, optional_delegate);

      // Printing Description of the created session object.
      System.out.printf("Session description:\n");
      System.out.printf("%s\n", session.Description());
      System.out.println();
      System.out.flush();
  
      // Creating an image object which will be used as an input for the session.
      OCRStudioSDKImage image = OCRStudioSDKImage.CreateFromFile(image_path);

      // Performing the recognition.
      session.ProcessImage(image);

      // Obtaining the recognition result.
      OCRStudioSDKResult result = session.CurrentResult();

      // Printing the contents of the recognition result.
      System.out.printf("Targets count: %d\n", result.TargetsCount());
      for (int i = 0; i < result.TargetsCount(); ++i) {
        OCRStudioSDKTarget target = result.TargetByIndex(i);
        System.out.printf("Target %d description:\n", i);
        System.out.printf("%s\n", target.Description());
        System.out.printf("\n");
        System.out.printf("Number of strings: %d\n", target.ItemsCountByType("string"));
        System.out.printf("Strings:\n");
        for (OCRStudioSDKItemIterator item_it = target.ItemsBegin("string"); !item_it.IsEqualTo(target.ItemsEnd("string")); item_it.Step()) {
          System.out.printf("  %s: %s\n\n", item_it.Item().Name(), item_it.Item().Description());
        }
        System.out.printf("Is target final: %s\n\n", (target.IsFinal() ? "true" : "false"));
        System.out.flush();
      }
      System.out.printf("Is result final: %s", (result.AllTargetsFinal() ? "true" : "false"));
      System.out.flush();

      // After the objects are no longer needed it is important to use the 
      // .delete() methods on them. It will force the associated native heap memory 
      // to be deallocated. Note that Java's GC does not care too much about the 
      // native heap and thus can delay the actual freeing of the associated memory, 
      // thus it is better to manage the internal native heap deallocation manually
      image.delete();
      result.delete();
      session.delete();
      engine_instance.delete();

    } catch (java.lang.Exception e) {
      System.out.printf("Exception thrown: %s\n", e.toString());
      System.out.flush();
      System.exit(-2);
    }
  }
}
