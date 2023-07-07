#include "DrawShapes_Custom_Viewport.h"
#include "AIS_Curve.h"
#include "AIS_Solid.h"

#include <WNT_Window.hxx>
#include <math.h>

#include <gp_Circ.hxx>
#include <GC_MakeArcOfCircle.hxx>

#include <BRepPrimAPI_MakeCone.hxx>

void DrawShapes_Custom_Viewport::Initialize(System::IntPtr handle)
{
    // create graphic driver
    Handle(Aspect_DisplayConnection) displayConnection;
    _graphicDriver() = new OpenGl_GraphicDriver(displayConnection);

    // create viewer 
    _viewer() = new V3d_Viewer(_graphicDriver());
    _viewer()->SetDefaultLights();
    _viewer()->SetLightOn();
    _viewer()->SetDefaultBackgroundColor(Quantity_NOC_BLACK);

    // create view (window os)
    auto wntWindow = new WNT_Window(reinterpret_cast<HWND>(handle.ToPointer()));
    _view() = _viewer()->CreateView();
    _view()->SetWindow(wntWindow);

    if (!wntWindow->IsMapped())
    {
        wntWindow->Map();
    }

    // create interactive context
    _aisContext() = new AIS_InteractiveContext(_viewer());
    _aisContext()->UpdateCurrentViewer();

    // update view
    _view()->Redraw();
    _view()->MustBeResized();
}

void DrawShapes_Custom_Viewport::Redraw()
{
    _view()->Redraw();
}

void DrawShapes_Custom_Viewport::UpdateResized()
{
    _view()->MustBeResized();
}

void DrawShapes_Custom_Viewport::ClearAll()
{
    _aisContext()->RemoveAll(false);
}

void DrawShapes_Custom_Viewport::DrawArc()
{
    gp_Ax2 wcs = gp::XOY();
    gp_Circ circle(wcs, 300.0);
    Handle(Geom_TrimmedCurve) arc = GC_MakeArcOfCircle(circle, 0.0, M_PI, false);
    Handle(AIS_Curve) shape = new AIS_Curve(arc);

    _aisContext()->Display(shape, false);
}

void DrawShapes_Custom_Viewport::DrawSolid()
{
    TopoDS_Shape cone = BRepPrimAPI_MakeCone(500.0, 0.0, 500.0);
    Handle(AIS_Solid) shape = new AIS_Solid(cone);

    _aisContext()->SetDisplayMode(2, false);
    _aisContext()->Display(shape, false);
}
