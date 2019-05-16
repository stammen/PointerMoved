#pragma once

namespace WindowsRuntimeComponent1
{
    public delegate void OnPointerMovedHandler(float x, float y);

    public ref class Class1 sealed
    {
    public:
        Class1();

        event OnPointerMovedHandler^ OnPointerMovedEvent;

    private:
        void OnPointerMoved(Windows::UI::Core::CoreWindow^ window, Windows::UI::Core::PointerEventArgs^ args);
    };
}
