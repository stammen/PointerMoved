// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#if defined(DLL_EXPORT)
#define DLL_EXPORT_API extern "C" __declspec(dllexport)
#else
#define DLL_EXPORT_API extern "C" __declspec(dllimport)
#endif

namespace WinRT
{
	typedef struct
	{
		float x;
		float y;
		unsigned int id;
	} PointerPointData;


    enum WinRTErrorType {
        WINRT_NO_ERROR = 0,                         //no error
        WINRT_WINDOWS_RUNTIME_ERROR,                // unable to initialize Windows Runtime
        WINRT_WINDOWS_VERSION_ERROR,                // this version of Windows does not support Windows::Services::Store
        WINRT_APP_PACKAGE_ERROR,                    // app is not running inside of an App Package
        WINRT_INITIALIZATION_ERROR,
		WINRT_INVALID_PARAMETER_ERROR,
		WINRT_MEMORY_ERROR,
		WINRT_UNSPECIFIED_ERROR
    };

    typedef void* InstancePtr;

    typedef void(__stdcall *PointerMovedCallback) (PointerPointData* data);

    typedef WinRTErrorType(__cdecl *InitializeFunc)(InstancePtr* instancePtr, PointerMovedCallback callback);
    DLL_EXPORT_API WinRTErrorType __cdecl Initialize(InstancePtr* instancePtr, PointerMovedCallback callback);
 
    typedef void(__cdecl *FreeFunc)(InstancePtr instancePtr);
    DLL_EXPORT_API void __cdecl Dispose(InstancePtr instancePtr);
};
 