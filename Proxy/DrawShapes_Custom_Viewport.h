#pragma once

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

#pragma comment(lib, "TKG2d.lib")
#pragma comment(lib, "TKG3d.lib")
#pragma comment(lib, "TKGeomBase.lib")
#pragma comment(lib, "TKPrim.lib")
#pragma comment(lib, "TKTopAlgo.lib")

public ref class DrawShapes_Custom_Viewport
{
public:
    void Initialize(System::IntPtr handle);
    void Redraw();
    void UpdateResized();

    void ClearAll();

    void DrawArc();
    void DrawSolid();

private:
    NCollection_Haft<Handle(V3d_Viewer)> _viewer;
    NCollection_Haft<Handle(V3d_View)> _view;
    NCollection_Haft<Handle(AIS_InteractiveContext)> _aisContext;
    NCollection_Haft<Handle(OpenGl_GraphicDriver)> _graphicDriver;
};

