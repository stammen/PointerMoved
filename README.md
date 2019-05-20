# PointerMoved

PointerMoved is an example of how to handle CoreWindow pointer moved events in C++ and pass the event data efficiently to a C# UWP app using a blittable struct.
In this example, we have used a C++ Windows Universal DLL instead of a WinRT Component to encapsulate the C++ pointer handing code. The ABI interface of a WinRT Component 
does not allow for the passing of a blittable struct. By using a C++ Windows Universal DLL, we are free to pass not WinRT types between the C# UWP app and the C++ DLL.

## Requirements

* Visual Studio 2017 with the following workloads installed

	* Universal Windows Platform development. Make sure you add the C++ workload.
	
## Setup Instructions


## Build and run PointerMoved

1. Open PointerMoved.sln

1. Make sure you have selected the x86 or x64 configuration. No not use the AnyCPU configuration.

1. Set the PointerMoved Project as the startup project

1. Press F5 to build and run the app.

1. Once the app appears, move your mouse. The event data will appear in the window.

## Debugging the PointerMoved App

We need to change the Debug properties of the PointerMoved project to use the Native Debugger.

* Right-click on the PointerMoved project.

* Select the Debug Tab

* Set Debugger Type | Application process to Mixed

* Set Debugger Type | Background task process to Mixed

You can now set breakpoints in the PointerMovedDLL project.

## Copying the PointerMovedDLL DLL to your App Package

In this sample, PointerMovedDLL.DLL is manually loaded by the PointerMoved app. We need to manually copy the PointerMovedDLL.DLL
to the correct location in the App Package. We can do this by modifying the XML of the PointerMoved.csproj project.

Add the following XML near the end of the PointerMoved.csproj (you can open this file with a text editor or Unload/Edit/Reload the file in Visual Studio)

```xml
  <ItemGroup>
    <Content Include="$(SolutionDir)$(Platform)/$(Configuration)/PointerMovedDLL/PointerMovedDLL.dll">
      <Link>PointerMovedDLL.dll</Link>
      <CopyToOutputDirectory>PreserveNewest</CopyToOutputDirectory>
    </Content>
    <Content Include="$(SolutionDir)$(Platform)/$(Configuration)/PointerMovedDLL/PointerMovedDLL.pdb">
      <Link>PointerMovedDLL.pdb</Link>
      <CopyToOutputDirectory>PreserveNewest</CopyToOutputDirectory>
    </Content>
  </ItemGroup>
```

This XML will automatically copy the correct build of the PointerMovedDLL.DLL to your App Package.

## Accessing Windows 10 APIs from a C++ Windows Universal DLL

In this example, we have used a C++ Windows Universal DLL instead of a WinRT Component. The ABI interface of a WinRT Component does not allow for the passing of a blittable struct. By
using a C++ Windows Universal DLL, we are free to pass not WinRT types between the C# UWP app and the C++ DLL.

Note: Under C/C++ | General set Consume Windows Runtime Extension to Yes(/ZW)

Make sure you make these property changes for All Configurations and All Platforms
 

##  Contributing

This project welcomes contributions and suggestions.  Most contributions require you to agree to a
Contributor License Agreement (CLA) declaring that you have the right to, and actually do, grant us
the rights to use your contribution. For details, visit https://cla.microsoft.com.

When you submit a pull request, a CLA-bot will automatically determine whether you need to provide
a CLA and decorate the PR appropriately (e.g., label, comment). Simply follow the instructions
provided by the bot. You will only need to do this once across all repos using our CLA.

This project has adopted the [Microsoft Open Source Code of Conduct](https://opensource.microsoft.com/codeofconduct/).
For more information see the [Code of Conduct FAQ](https://opensource.microsoft.com/codeofconduct/faq/) or
contact [opencode@microsoft.com](mailto:opencode@microsoft.com) with any additional questions or comments.


## Reporting Security Issues

Security issues and bugs should be reported privately, via email, to the Microsoft Security
Response Center (MSRC) at [secure@microsoft.com](mailto:secure@microsoft.com). You should
receive a response within 24 hours. If for some reason you do not, please follow up via
email to ensure we received your original message. Further information, including the
[MSRC PGP](https://technet.microsoft.com/en-us/security/dn606155) key, can be found in
the [Security TechCenter](https://technet.microsoft.com/en-us/security/default).
