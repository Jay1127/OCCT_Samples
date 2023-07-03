#pragma once

#using <system.drawing.dll>

#include <Standard_Handle.hxx>
#include <V3d_Viewer.hxx>
#include <V3d_View.hxx>
#include <AIS_InteractiveContext.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <NCollection_Haft.h>

// list of required OCCT libraries
#pragma comment(lib, "TKernel.lib")
#pragma comment(lib, "TKMath.lib")
#pragma comment(lib, "TKBRep.lib")
#pragma comment(lib, "TKXSBase.lib")
#pragma comment(lib, "TKService.lib")
#pragma comment(lib, "TKV3d.lib")
#pragma comment(lib, "TKOpenGl.lib")
#pragma comment(lib, "TKVrml.lib")
#pragma comment(lib, "TKLCAF.lib")

public ref class HelloOCCT_Viewport
{
public:
	bool Initialize(System::IntPtr handle);
	void Update();
	void SetBackgroudColor(System::Drawing::Color backgroundColor);

private:
	NCollection_Haft<Handle(V3d_Viewer)> _viewer;
	NCollection_Haft<Handle(V3d_View)> _view;
	NCollection_Haft<Handle(AIS_InteractiveContext)> _aisContext;
	NCollection_Haft<Handle(OpenGl_GraphicDriver)> _graphicDriver;
};

