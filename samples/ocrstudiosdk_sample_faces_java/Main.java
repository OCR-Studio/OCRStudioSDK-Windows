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

  public static void main(String[] args) {

    // 1st argument - path to the first image for face comparison
    // 2nd argument - path to the second image for face comparison
    // 3rd argument - path to configuration config
    if (args.length != 3) {
      System.out.printf("Version %s. Usage: ocrstudiosdk_sample_faces_java " + 
          " <image_path_lvalue> <image_path_rvalue> <config_path>\n", 
          OCRStudioSDKInstance.LibraryVersion());
      System.exit(-1);
    }

    String image_path_lvalue = args[0];
    String image_path_rvalue = args[1];
    String config_path = args[2];

    System.out.printf("OCRStudioSDK version %s\n", 
                      OCRStudioSDKInstance.LibraryVersion());
    System.out.printf("image_path_lvalue = %s\n", image_path_lvalue);
    System.out.printf("image_path_rvalue = %s\n", image_path_rvalue);
    System.out.printf("config_path = %s\n", config_path);
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
      session_params += "\"session_type\": \"face_matching\", ";
      session_params += "\"target_group_type\": \"default\"";
      session_params += "}";


      // Creating a session object - a main handle for performing
      //     face matching. Note you should put your SDK signature 
      //     verification as the first parameter.
      OCRStudioSDKSession session = engine_instance.CreateSession({put_your_personalized_signature_from_doc_README.md}, session_params);

      // Printing Description of the created session object.
      System.out.printf("Session description:\n");
      System.out.printf("%s\n", session.Description());
      System.out.println();
      System.out.flush();
  
      // Creating image objects which will be used for face matching.
      OCRStudioSDKImage image_lvalue = OCRStudioSDKImage.CreateFromFile(image_path_lvalue);
      OCRStudioSDKImage image_rvalue = OCRStudioSDKImage.CreateFromFile(image_path_rvalue);

      // Performing face matching between two images.
      session.ProcessImage(image_lvalue);
      session.ProcessImage(image_rvalue);

      // Obtaining the face matching result.
      OCRStudioSDKResult result = session.CurrentResult();

      // Printing the contents of the face matching result.
      OCRStudioSDKTarget target = result.TargetByIndex(0);
      System.out.printf("Target description:\n");
      System.out.printf("%s\n", target.Description());
      System.out.println();
      System.out.printf("Items:\n");
      for (OCRStudioSDKItemIterator item_it = target.ItemsBegin("string"); !item_it.IsEqualTo(target.ItemsEnd("string")); item_it.Step()) {
        System.out.printf("  %s: %s\n", item_it.Item().Name(), item_it.Item().Value());
      }
      System.out.flush();

      // After the objects are no longer needed it is important to use the 
      // .delete() methods on them. It will force the associated native heap memory 
      // to be deallocated. Note that Java's GC does not care too much about the 
      // native heap and thus can delay the actual freeing of the associated memory, 
      // thus it is better to manage the internal native heap deallocation manually
      image_lvalue.delete();
      image_rvalue.delete();
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
