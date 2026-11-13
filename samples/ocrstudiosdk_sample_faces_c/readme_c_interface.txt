# C Wrapper for OCRStudioSDK
# 
# OCRStudioSDK has C API which is wrapped from C++ interface.
# The C API is a complete wrap of the C++ interface, the differences are based on the rules how each type is owned and managed.
# 
# Wrapping Principles
# 1. POD Types
# If a C++ struct has no non-trivial destructor, it is not opaque in the C API, instead an еquivalent plain C struct is declared and used directly.
#
# 2. Exclusively Client-Owned Types
# If the C++ type's memory is always owned by the caller, it is wrapped as an opaque handle.
# 
# 3. Exclusively Library-Owned Types
# If thе C++ type's memory is managed entirely by the library, it is wrapped as an opaque Ref Handle - the caller never owns or frees it.
# 
# 4. Shared-Ownership Types
# Types that may be owned by either the caller or the library are wrapped as regular handles and expose both a handle and a Ref handle.
# 
# 5. Abstract Classes with Callback Interfaces
# Abstract C++ classes used as callback interfaces are not exposed in the C API.
# 
# Usage 
# Link against 'libcocrstudiosdk.so' and include the C headers. For additional context please see the provided C sample.
