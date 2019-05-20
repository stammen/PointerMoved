using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409


namespace PointerMoved
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        // Declares a managed structure for each unmanaged structure.
        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
        public struct PointerPointData
        {
            public float x;
            public float y;
            public uint id;
        }

        public delegate void PointerMovedCallBack(ref PointerPointData data);


        [DllImport("PointerMovedDLL.dll", CharSet = CharSet.Unicode, SetLastError = true)]
        private static extern int Initialize(ref IntPtr instancePtr, PointerMovedCallBack callback);

        private IntPtr m_pointerMoved;

        public MainPage()
        {
            this.InitializeComponent();
            var result = Initialize(ref m_pointerMoved, OnPointerMoved);
        }

        private void OnPointerMoved(ref PointerPointData data)
        {
            pointerMovedText.Text = "X:" + data.x + " Y:" + data.y + " ID:" + data.id;
        }
    }
}
