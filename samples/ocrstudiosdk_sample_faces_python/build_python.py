from zipfile import ZipFile
import glob, os, sys, subprocess

def print_usage():
   print("usage: python build_python.py <platform_name>\n")
   print("\twhere <platform_name> 'Win32' optional")

if os.path.exists("SWIG-4.1.1_Windows.zip"):
   zip_name = "SWIG-4.1.1_Windows.zip"
   with ZipFile(zip_name, 'r') as zipObj:
      zipObj.extractall()
   root = sys.path[0]
   swig_executable = "-DSWIG_EXECUTABLE=" + os.path.join(root, "SWIG", "bin", "swig")
   swig_dir = "-DSWIG_DIR=" + os.path.join(root, "SWIG", "share", "swig", "4.1.1")
else:
   zip_name = glob.glob("swigwin-*.zip")[0]
   with ZipFile(zip_name, 'r') as zipObj:
      zipObj.extractall()
   root = sys.path[0]
   swig_root = os.path.splitext(zip_name)[0]
   swig_executable = "-DSWIG_EXECUTABLE=" + os.path.join(root, swig_root, "swig")
   swig_dir = "-DSWIG_DIR=" + os.path.join(root, swig_root, "Lib")

first_arg = ''

if len(sys.argv) > 1:
   if sys.argv[1] == '-h':
      print_usage()
      sys.exit(-1)
   else:
      first_arg = sys.argv[1]
      print(first_arg)

library_path="-DOCRSTUDIOSDK_LIBRARY_PATH=" + os.path.join(root, "..","..","lib")

os.mkdir("build")
os.chdir("build")

# https://cmake.org/cmake/help/latest/generator/Visual%20Studio%2017%202022.html#platform-selection
if first_arg == 'Win32':
   subprocess.run(["CMAKE", "-G", "Visual Studio 17 2022", "-A Win32", "..", swig_executable,swig_dir,library_path ])
else:
   subprocess.run(["CMAKE", "-G", "Visual Studio 17 2022", "-A x64" , "..", swig_executable,swig_dir,library_path ])
subprocess.run(["cmake", "--build", ".", "--config", "Debug", "--target", "INSTALL"])
subprocess.run(["cmake", "--build", ".", "--config", "Release", "--target", "INSTALL"])
