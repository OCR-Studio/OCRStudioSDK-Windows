#  Copyright (c) 2024-2026, OCR Studio
#  All rights reserved.

#!/usr/bin/python
import sys
import os

sys.path.append(os.path.join(sys.path[0], '../../bindings/python/'))
sys.path.append(os.path.join(sys.path[0],'../../bin/'))

import ocrstudiosdk

#class OptionalDelegate(ocrstudiosdk.OCRStudioSDKDelegate):
#
#  def Callback(self, json_message):
#    print("[Feedback called]:\n%s\n".format(json_message))


def main():
  if len(sys.argv) != 4:
    print('Version {}. Usage: '
            '{} <image_path> <config_path> <target_mask>'.format(
            ocrstudiosdk.OCRStudioSDKInstance.LibraryVersion(), sys.argv[0]))
    sys.exit(-1)

  image_path = sys.argv[1]
  config_path = sys.argv[2]
  target_mask = sys.argv[3]

  print('OCRStudioSDK version {}'.format(
         ocrstudiosdk.OCRStudioSDKInstance.LibraryVersion()))
  print('image_path = {}'.format( image_path))
  print('config_path = {}'.format( config_path))
  print('target_mask = {}'.format( target_mask))
  print('')

  #optional_delegate = OptionalDelegate()

  try:
    # Creating the recognition engine object - initializes all internal
    #     configuration structure. Second parameter to the factory method
    #     is the optional JSON with initialization parameters (see documentation).
    engine_instance = ocrstudiosdk.OCRStudioSDKInstance.CreateFromPath(config_path)

    # Printing Description of the created engine object.
    print('Engine instance description:')
    print(engine_instance.Description())
    print('')

    # Parameters necessary for session creation.
    session_params = "{"
    session_params += "\"session_type\": \"document_recognition\", "
    session_params += "\"target_group_type\": \"default\", "
    session_params += "\"target_masks\": \"" + target_mask + "\", "
    session_params += "\"output_modes\": ["
    session_params += "\"character_alternatives\", "
    session_params += "\"field_geometry\" "
    session_params += "] "
    session_params += "}"

    # Creating a session object - a main handle for performing recognition.
    #   Note you should put your SDK signature verification as the first parameter.
    session = engine_instance.CreateSession({put_your_personalized_signature_from_doc_README.md}, session_params)

    # Printing Description of the created session object.
    print('Session description:')
    print(session.Description())
    print('')

    # Creating an image object which will be used as an input for the session.
    image = ocrstudiosdk.OCRStudioSDKImage.CreateFromFile(image_path)

    # Performing the recognition.
    session.ProcessImage(image)

    # Obtaining the recognition result.
    result = session.CurrentResult()

    # Printing the contents of the recognition result.
    print('Targets count: {}'.format(result.TargetsCount()))
    for i in range(result.TargetsCount()):
      target = result.TargetByIndex(i)
      print('Target {} description:'.format(i))
      print(target.Description())
      print('')
      print('Number of strings: {}'.format(target.ItemsCountByType('string')))
      print('Strings:')
      item_it = target.ItemsBegin('string')
      while not item_it.IsEqualTo(target.ItemsEnd('string')):
        print('  {}: {}\n'.format(item_it.Item().Name(), item_it.Item().Description()))
        item_it.Step()

      print('Is target final: {}\n'.format('true' if target.IsFinal() else 'false'))

      print('Is result final: {}'.format('true' if result.AllTargetsFinal() else 'false'))    
  except BaseException as e: 
    print('Exception thrown: {}'.format(e))
    return -1

  return 0


if __name__ == '__main__':
    main()
