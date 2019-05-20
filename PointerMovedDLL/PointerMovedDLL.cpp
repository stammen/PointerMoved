// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"
#include "PointerMovedDLL.h"
#include "PointerMovedImpl.h"
#include <appmodel.h>
#include <roapi.h>

namespace WinRT
{

	WinRTErrorType Initialize(InstancePtr* instancePtr, PointerMovedCallback callback)
	{
		*instancePtr = nullptr;
		
		PointerMovedImpl* instance = new PointerMovedImpl();
		WinRTErrorType result = instance->Initialize(callback);
		if (result != WINRT_NO_ERROR)
		{
			delete instance;
			*instancePtr = nullptr;
		}
		else
		{
			*instancePtr = (InstancePtr)instance;
		}

		return result;
	}

	void Dispose(InstancePtr instancePtr)
	{
		if (instancePtr)
		{
			delete instancePtr;
		}
	}
}

