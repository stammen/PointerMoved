#include "pch.h"
#include "Class1.h"

using namespace WindowsRuntimeComponent1;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::System;

using namespace Windows::UI::Core;

Class1::Class1()
{
    auto window = CoreWindow::GetForCurrentThread();
    window->PointerMoved += ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &Class1::OnPointerMoved);
}



void Class1::OnPointerMoved(CoreWindow^ window, PointerEventArgs^ args)
{
    OnPointerMovedEvent(args->CurrentPoint->Position.X, args->CurrentPoint->Position.Y);
}

