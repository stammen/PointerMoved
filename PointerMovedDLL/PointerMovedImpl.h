// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include "PointerMovedDLL.h"
#include "DeviceResources.h"
#include <memory>
namespace WinRT
{
    class PointerMovedImpl
    {
    public:
		PointerMovedImpl();
        ~PointerMovedImpl();
        WinRTErrorType Initialize(PointerMovedCallback callback, Windows::UI::Xaml::Controls::SwapChainPanel ^swapChainPanel);

    private:
		Windows::Foundation::EventRegistrationToken m_token;
		void OnPointerMoved(Platform::Object^ object, Windows::UI::Core::PointerEventArgs^ args);
		PointerMovedCallback m_callback;
        Windows::UI::Core::CoreIndependentInputSource^ _coreIndependentInput;
        Windows::Foundation::IAsyncAction^ _inputLoopWorker;
        std::shared_ptr<DX::DeviceResources> m_deviceResources;
        void PointerMovedImpl::StartRenderLoop();
        Windows::Foundation::IAsyncAction^ m_renderLoopWorker;
        void OnSwapChainPanelSizeChanged(Platform::Object^ sender, Windows::UI::Xaml::SizeChangedEventArgs^ e);
    };
};

