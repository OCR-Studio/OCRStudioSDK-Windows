%module ocrstudiosdk
%feature("director") ocrstudio::OCRStudioSDKDelegate;

%include typemaps.i
%include exception.i
%include std_except.i
%include std_map.i
%include std_string.i
%include std_vector.i
%include stdint.i

%{
  #include "ocrstudiosdk/ocr_studio_delegate.h"
  #include "ocrstudiosdk/ocr_studio_exception.h"
  #include "ocrstudiosdk/ocr_studio_export.h"
  #include "ocrstudiosdk/ocr_studio_image.h"
  #include "ocrstudiosdk/ocr_studio_processing_config.h"
  #include "ocrstudiosdk/ocr_studio_instance.h"
  #include "ocrstudiosdk/ocr_studio_result.h"
  #include "ocrstudiosdk/ocr_studio_session.h"
  #include "ocrstudiosdk/ocr_studio_string.h"
%}

%rename("%(lowercamelcase)s", %$isvariable) "";

%exception {
  try {
    $action
  } catch (const ocrstudio::OCRStudioSDKException& e) {
        SWIG_exception(SWIG_RuntimeError, (std::string("CRITICAL!: ") + std::string(e.Type()) + " exception caught: " + e.Message()).c_str());
  } catch (const std::exception& e) {
        SWIG_exception(SWIG_RuntimeError, (std::string("CRITICAL!: STL exception caught: ") + e.what()).c_str());
  } catch (...) {
        SWIG_exception(SWIG_RuntimeError, "CRITICAL!: Unknown exception caught");
  }
}

%newobject ocrstudio::OCRStudioSDKImage::CreateEmpty;
%newobject ocrstudio::OCRStudioSDKImage::CreateFromFile;
%newobject ocrstudio::OCRStudioSDKImage::CreateFromFileBuffer;
%newobject ocrstudio::OCRStudioSDKImage::CreateFromBase64FileBuffer;
%newobject ocrstudio::OCRStudioSDKImage::CreateFromPixelBuffer;
%newobject ocrstudio::OCRStudioSDKImage::CreateFromYUVSimple;
%newobject ocrstudio::OCRStudioSDKImage::CreateFromYUV;
%newobject ocrstudio::OCRStudioSDKImage::DeepCopy;
%newobject ocrstudio::OCRStudioSDKImage::ShallowCopy;
%newobject ocrstudio::OCRStudioSDKImage::DeepCopyScaled;
%newobject ocrstudio::OCRStudioSDKImage::DeepCopyCroppedByQuad;
%newobject ocrstudio::OCRStudioSDKImage::DeepCopyCroppedByRect;
%newobject ocrstudio::OCRStudioSDKImage::ShallowCopyCroppedByRect;
%newobject ocrstudio::OCRStudioSDKImage::DeepCopyRotatedByNinety;

%newobject ocrstudio::OCRStudioSDKInstance::CreateStandalone;
%newobject ocrstudio::OCRStudioSDKInstance::CreateFromPath;
%newobject ocrstudio::OCRStudioSDKInstance::CreateFromBuffer;
%newobject ocrstudio::OCRStudioSDKInstance::CreateSession;

%newobject ocrstudio::OCRStudioSDKTarget::DeepCopy;
%newobject ocrstudio::OCRStudioSDKResult::DeepCopy;

%ignore OCRStudioSDKItemIteratorImplementation;
%ignore CreateFromImplementation;


%include ocrstudiosdk/ocr_studio_export.h
%include ocrstudiosdk/ocr_studio_delegate.h
%include ocrstudiosdk/ocr_studio_exception.h
%include ocrstudiosdk/ocr_studio_string.h
%include ocrstudiosdk/ocr_studio_image.h
%include ocrstudiosdk/ocr_studio_processing_config.h
%include ocrstudiosdk/ocr_studio_result.h
%include ocrstudiosdk/ocr_studio_session.h
%include ocrstudiosdk/ocr_studio_instance.h
