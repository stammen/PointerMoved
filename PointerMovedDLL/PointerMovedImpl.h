// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include "PointerMovedDLL.h"

namespace WinRT
{
    class PointerMovedImpl
    {
    public:
		PointerMovedImpl();
        ~PointerMovedImpl();
        WinRTErrorType Initialize(PointerMovedCallback callback);

    private:
		Windows::Foundation::EventRegistrationToken m_token;
		void OnPointerMoved(Windows::UI::Core::CoreWindow^ window, Windows::UI::Core::PointerEventArgs^ args);
		PointerMovedCallback m_callback;
    };
};

