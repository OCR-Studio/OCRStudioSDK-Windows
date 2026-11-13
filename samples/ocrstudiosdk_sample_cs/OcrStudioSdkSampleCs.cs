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
    Console.WriteLine("[Feedback called]:\n{0}\n", json_message);
  }
};


class OcrStudioSdkSampleCs
{
  static void Main(string[] args)
  {
    // 1st argument - path to the image to be recognized
    // 2nd argument - path to the configuration config
    // 3rd argument - target mask
    if (args.Length != 3) {
      Console.WriteLine("Version {0}. Usage: " +
             "OcrStudioSdkSampleCs_cs <image_path> <config_path> <target_mask>\n",
          ocrstudio.OCRStudioSDKInstance.LibraryVersion());
      Console.WriteLine(Environment.NewLine);
      return;
    }
  
    String image_path = args[0];
    String config_path = args[1];
    String target_mask = args[2];
  
    Console.WriteLine("OCRStudioSDK version {0}\n",
           ocrstudio.OCRStudioSDKInstance.LibraryVersion());
    Console.WriteLine("image_path = {0}\n", image_path);
    Console.WriteLine("config_path = {0}\n", config_path);
    Console.WriteLine("target_mask = {0}\n", target_mask);
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
      ocrstudio.OCRStudioSDKSession session = 
          engine_instance.CreateSession({put_your_personalized_signature_from_doc_README.md}, session_params, optional_delegate);
  
      // Printing Description of the created session object.
      Console.WriteLine("Session description:\n");
      Console.WriteLine("{0}\n", session.Description());
      Console.WriteLine("\n");

      // Creating an image object which will be used as an input for the session.
      ocrstudio.OCRStudioSDKImage image;

      image = ocrstudio.OCRStudioSDKImage.CreateFromFile(image_path);

      // Performing the recognition.
      session.ProcessImage(image);

      // Obtaining the recognition result.
      ocrstudio.OCRStudioSDKResult result = session.CurrentResult();
  
      // Printing the contents of the recognition result.
      Console.WriteLine("Targets count: {0}\n", result.TargetsCount());
      for (int i = 0; i < result.TargetsCount(); ++i) {
        ocrstudio.OCRStudioSDKTarget target = result.TargetByIndex(i);
        Console.WriteLine("Target {0} description:\n", i);
        Console.WriteLine("{0}\n", target.Description());
        Console.WriteLine("\n");
        Console.WriteLine("Number of strings: {0}\n", target.ItemsCountByType("string"));
        Console.WriteLine("Strings:\n");
        for (OCRStudioSDKItemIterator it = target.ItemsBegin("string"); !it.IsEqualTo(target.ItemsEnd("string")); it.Step()) {
          Console.WriteLine("  {0}: {1}\n\n", it.Item().Name(), it.Item().Description());
        }
        Console.WriteLine("Is target final: {0}\n\n",
                (target.IsFinal() ? "true" : "false"));
      }
      Console.WriteLine("Is result final: {0}",
              (result.AllTargetsFinal() ? "true" : "false"));

      // this is important: GC works differently with native-heap objects
      image.Dispose();
      result.Dispose();
      session.Dispose();
      engine_instance.Dispose();
    }
    catch (Exception e)
    {
      Console.WriteLine("Exception caught: {0}", e);
    }

    Console.WriteLine("Processing ended");
  }

}

