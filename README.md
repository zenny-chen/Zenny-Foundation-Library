# Zenny Foundation Library
A lightweight and cross-platform pure C library.

It contains some basic containers which are based on reference counting. It also supplies a lot of useful cross-platform utilities.

## Compilers requirement:
MSVC v14 with Visual Studio 2017 or later

GCC v4.9 or later

Clang v3.8 or later

If you're using Windows platform, Windows 10 is preferred. If you compile the project with GCC or Clang, just use `-std=gnu11` compile option.

If you're using Visual Studio IDE, add the following include directory to your project: `$(LocalDebuggerWorkingDirectory)\zenny_foundation;$(LocalDebuggerWorkingDirectory)\zenny_foundation\zf_sys;`
Also, you should add `_CRT_SECURE_NO_WARNINGS` in the preprocessing definitions. 
