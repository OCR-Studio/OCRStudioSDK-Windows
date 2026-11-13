/**
  Copyright (c) 2024-2026, OCR Studio
  All rights reserved.
*/

using System;
using System.Text;

using ocrstudio;

class OptionalDelegate : ocrstudio.OCRStudioSDKDelegate {
  public OptionalDelegate() : base()
  {
  }

  public override void Callback(string json_message)  {
    Console.WriteLine("[Feedback called]:\n%s\n", json_message);
  }
};


class OcrStudioSdkSampleCs
{
  static void Main(string[] args)
  {
    // 1st argument - path to the first image for face comparison
  // 2nd argument - path to the second image for face comparison
  // 3rd argument - path to configuration config
    if (args.Length != 3) {
      Console.WriteLine("Version {0}. Usage: " +
             "OcrStudioSdkSampleCs_faces_cs <image_path_lvalue> <image_path_rvalue> <config_path>\n",
          ocrstudio.OCRStudioSDKInstance.LibraryVersion());
      Console.WriteLine(Environment.NewLine);
      return;
    }
  
    String image_path_lvalue = args[0];
    String image_path_rvalue = args[1];
    String config_path = args[2];
  
    Console.WriteLine("OCRStudioSDK version {0}\n",
           ocrstudio.OCRStudioSDKInstance.LibraryVersion());
    Console.WriteLine("image_path_lvalue = {0}\n", image_path_lvalue);
    Console.WriteLine("image_path_rvalue = {0}\n", image_path_rvalue);
    Console.WriteLine("config_path = {0}\n", config_path);
    Console.WriteLine("\n");

    try
    {
      OptionalDelegate optional_delegate = new OptionalDelegate();

      // Creating the recognition engine object - initializes all internal
      //     configuration structure. Second parameter to the factory method
      //     is the optional JSON with initialization parameters (see documentation).
      ocrstudio.OCRStudioSDKInstance engine_instance = 
          ocrstudio.OCRStudioSDKInstance.CreateFromPath(config_path);
  
      // Printing Description of the created engine object.
      Console.WriteLine("Engine instance description:\n");
      Console.WriteLine("{0}\n", engine_instance.Description());
      Console.WriteLine("\n");
  
      // Parameters necessary for session creation.
      String session_params = "{";
      session_params += "\"session_type\": \"face_matching\", ";
      session_params += "\"target_group_type\": \"default\"";
      session_params += "}";

      // Creating a session object - a main handle for performing
      //     face matching. Note you should put your SDK signature 
      //     verification as the first parameter.
      ocrstudio.OCRStudioSDKSession session = 
          engine_instance.CreateSession({put_your_personalized_signature_from_doc_README.md}, session_params, optional_delegate);
  
      // Printing Description of the created session object.
      Console.WriteLine("Session description:\n");
      Console.WriteLine("{0}\n", session.Description());
      Console.WriteLine("\n");

      // Creating image objects which will be used for face matching.
      ocrstudio.OCRStudioSDKImage image_lvalue;
      ocrstudio.OCRStudioSDKImage image_rvalue;
      image_lvalue = ocrstudio.OCRStudioSDKImage.CreateFromFile(image_path_lvalue);
      image_rvalue = ocrstudio.OCRStudioSDKImage.CreateFromFile(image_path_rvalue);

      // Performing face matching between two images.
      session.ProcessImage(image_lvalue);
      session.ProcessImage(image_rvalue);

      // Obtaining the face matching result.
      ocrstudio.OCRStudioSDKResult result = session.CurrentResult();
  
      // Printing the contents of the face matching result.
      ocrstudio.OCRStudioSDKTarget target = result.TargetByIndex(0);
      Console.WriteLine("Target description:\n");
      Console.WriteLine("{0}\n", target.Description());
      Console.WriteLine("\n");
      Console.WriteLine("Items:");
      for (OCRStudioSDKItemIterator it = target.ItemsBegin("string"); !it.IsEqualTo(target.ItemsEnd("string")); it.Step()) {
        Console.WriteLine("  {0}: {1}", it.Item().Name(), it.Item().Value());
      }

      // this is important: GC works differently with native-heap objects
      image_lvalue.Dispose();
      image_rvalue.Dispose();
      result.Dispose();
      session.Dispose();
      engine_instance.Dispose();
    }
    catch (Exception e)
    {
      Console.WriteLine("\nException caught: {0}", e);
    }

    Console.WriteLine("\nProcessing ended");
  }

}

