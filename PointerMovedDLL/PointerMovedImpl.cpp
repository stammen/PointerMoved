// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"
#include "PointerMovedImpl.h"
#include <string>
#include <functional>

using namespace WinRT;
using namespace Windows::Foundation;
using namespace Windows::System::Threading;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml;
using namespace std::placeholders;

PointerMovedImpl::PointerMovedImpl()
{}

PointerMovedImpl::~PointerMovedImpl()
{
    auto window = CoreWindow::GetForCurrentThread();
    if (window != nullptr)
    {
        window->PointerMoved -= m_token;
    }
}

WinRTErrorType PointerMovedImpl::Initialize(PointerMovedCallback callback, Windows::UI::Xaml::Controls::SwapChainPanel ^swapChainPanel)
{
    WinRTErrorType result = WINRT_NO_ERROR;
    m_callback = callback;

    m_deviceResources = std::make_shared<DX::DeviceResources>();
    m_deviceResources->SetSwapChainPanel(swapChainPanel);

    WorkItemHandler ^handler = ref new WorkItemHandler([this, swapChainPanel](IAsyncAction^ operation) {
        //Setup a Core independent Input
        _coreIndependentInput = swapChainPanel->CreateCoreIndependentInputSource(
            CoreInputDeviceTypes::Pen |
            CoreInputDeviceTypes::Touch |
            CoreInputDeviceTypes::Mouse);
        //_coreIndependentInput->SetPointerCapture();
        _coreIndependentInput->PointerMoved += ref new TypedEventHandler<Platform::Object^, PointerEventArgs^>(std::bind(&PointerMovedImpl::OnPointerMoved, this, _1, _2));
        _coreIndependentInput->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessUntilQuit);    // start processing touch events
        });

    _inputLoopWorker = ThreadPool::RunAsync(
        handler,
        WorkItemPriority::Normal,
        WorkItemOptions::TimeSliced
    );

    swapChainPanel->SizeChanged += ref new SizeChangedEventHandler(std::bind(&PointerMovedImpl::OnSwapChainPanelSizeChanged, this, _1, _2));
    //StartRenderLoop();
    return result;
}

void PointerMovedImpl::OnSwapChainPanelSizeChanged(Platform::Object^ sender, Windows::UI::Xaml::SizeChangedEventArgs^ e)
{
    m_deviceResources->SetLogicalSize(e->NewSize);
    m_deviceResources->Present();

}

void PointerMovedImpl::OnPointerMoved(Platform::Object^ object, Windows::UI::Core::PointerEventArgs^ args)
{
    if (m_callback)
    {
        PointerPointData d;
        d.x = args->CurrentPoint->Position.X;
        d.y = args->CurrentPoint->Position.Y;
        d.id = args->CurrentPoint->PointerId;
        m_callback(&d);
    }
}

void PointerMovedImpl::StartRenderLoop()
{
    // If the animation render loop is already running then do not start another thread.
    if (m_renderLoopWorker != nullptr && m_renderLoopWorker->Status == AsyncStatus::Started)
    {
        return;
    }

    // Create a task that will be run on a background thread.
    auto workItemHandler = ref new WorkItemHandler([this](IAsyncAction ^ action)
        {
            auto w = m_deviceResources->GetScreenViewport();
            m_deviceResources->Present();

        });

    // Run task on a dedicated high priority background thread.
    m_renderLoopWorker = ThreadPool::RunAsync(workItemHandler, WorkItemPriority::High, WorkItemOptions::TimeSliced);
}





