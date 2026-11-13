#  Copyright (c) 2024-2026, OCR Studio
#  All rights reserved.

#!/usr/bin/python
import sys
import os

sys.path.append(os.path.join(sys.path[0], '../../bindings/python/'))
sys.path.append(os.path.join(sys.path[0],'../../bin/'))

import ocrstudiosdk

def main():
  if len(sys.argv) != 4:
    print('Version {}. Usage: '
            '{} <image_path_lvalue> <image_path_rvalue> <config_path>'.format(
            ocrstudiosdk.OCRStudioSDKInstance.LibraryVersion(), sys.argv[0]))
    sys.exit(-1)

  image_path_lvalue = sys.argv[1]
  image_path_rvalue = sys.argv[2]
  config_path = sys.argv[3]

  print('OCRStudioSDK version {}'.format(
         ocrstudiosdk.OCRStudioSDKInstance.LibraryVersion()))
  print('image_path_lvalue = {}'.format( image_path_lvalue))
  print('image_path_rvalue = {}'.format( image_path_rvalue))
  print('config_path = {}'.format( config_path))
  print('')

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
    session_params += "\"session_type\": \"face_matching\", "
    session_params += "\"target_group_type\": \"default\" "
    session_params += "}"

    # Creating a session object - a main handle for performing
    #     face matching. Note you should put your SDK signature 
    #     verification as the first parameter.
    session = engine_instance.CreateSession({put_your_personalized_signature_from_doc_README.md}, session_params)

    # Printing Description of the created session object.
    print('Session description:')
    print(session.Description())
    print('')

    # Creating image objects which will be used for face matching.
    image_lvalue = ocrstudiosdk.OCRStudioSDKImage.CreateFromFile(image_path_lvalue)
    image_rvalue = ocrstudiosdk.OCRStudioSDKImage.CreateFromFile(image_path_rvalue)

    # Performing face matching between two images.
    session.ProcessImage(image_lvalue)
    session.ProcessImage(image_rvalue)

    # Obtaining the face matching result.
    result = session.CurrentResult()

    # Printing the contents of the face matching result.
    target = result.TargetByIndex(0)
    print('Target description:')
    print(target.Description())
    print("Items:")
    item_it = target.ItemsBegin('string')
    while not item_it.IsEqualTo(target.ItemsEnd('string')):
      print('  {}: {}'.format(item_it.Item().Name(), item_it.Item().Value()))
      item_it.Step()
  except BaseException as e: 
    print('Exception thrown: {}'.format(e))
    return -1

  return 0


if __name__ == '__main__':
    main()
