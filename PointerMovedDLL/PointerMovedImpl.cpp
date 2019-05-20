// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"
#include "PointerMovedImpl.h"
#include <string>
#include <functional>

using namespace WinRT;
using namespace Windows::Foundation;
using namespace Windows::UI::Core;
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

WinRTErrorType PointerMovedImpl::Initialize(PointerMovedCallback callback)
{
    WinRTErrorType result = WINRT_NO_ERROR;
    m_callback = callback;

    auto window = CoreWindow::GetForCurrentThread();
    if (window != nullptr)
    {
        // Note: This uses std:bind to bind the event handler as this is a normal C++ class and not a WinRT class
        m_token = window->PointerMoved += ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(std::bind(&PointerMovedImpl::OnPointerMoved, this, _1, _2));
    }
    else
    {
        result = WINRT_INITALIZATION_ERROR;
    }

    return result;
}

void PointerMovedImpl::OnPointerMoved(Windows::UI::Core::CoreWindow^ window, Windows::UI::Core::PointerEventArgs^ args)
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





