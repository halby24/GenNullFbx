#ifndef GEN_NULL_FBX_H
#define GEN_NULL_FBX_H

#define DLLEXPORT extern "C" __declspec(dllexport)

DLLEXPORT int __stdcall GenNullFbx(const char* pFilePath, bool pVerbose);

#endif