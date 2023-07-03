#include "DrawShapes_Viewport.h"

#include <math.h>
#include <WNT_Window.hxx>

#include <Geom_CartesianPoint.hxx>
#include <Geom_Line.hxx>
#include <Geom_Circle.hxx>
#include <Geom_Plane.hxx>

#include <GC_MakeLine.hxx>
#include <GC_MakeCircle.hxx>
#include <GC_MakePlane.hxx>

#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>

#include <AIS_Point.hxx>
#include <AIS_Line.hxx>
#include <AIS_Circle.hxx>
#include <AIS_Axis.hxx>
#include <AIS_TextLabel.hxx>
#include <AIS_Plane.hxx>
#include <AIS_Shape.hxx>

bool DrawShapes_Viewport::Initialize(System::IntPtr handle)
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

    return false;
}

void DrawShapes_Viewport::Redraw()
{
    _view()->Redraw();
}

void DrawShapes_Viewport::UpdateResized()
{
    _view()->MustBeResized();
}

void DrawShapes_Viewport::ClearAll()
{
    _aisContext()->RemoveAll(false);
}

void DrawShapes_Viewport::DrawLine()
{
    gp_Pnt startPt(0, 0, 0);
    gp_Pnt endPt(100, 100, 100);
    Handle(Geom_Line) line = GC_MakeLine(startPt, endPt);
    Handle(AIS_Line) shape = new AIS_Line(line);

    _aisContext()->Display(shape, false);
}

void DrawShapes_Viewport::DrawSegment()
{
    Handle(Geom_Point) startPt = new Geom_CartesianPoint(0, 0, 0);
    Handle(Geom_Point) endPt = new Geom_CartesianPoint(100, 100, 100);
    Handle(AIS_Line) shape = new AIS_Line(startPt, endPt);

    _aisContext()->Display(shape, false);
}

void DrawShapes_Viewport::DrawCircle()
{
    gp_Ax1 zAxis = gp::OZ();
    Handle(Geom_Circle) circle = GC_MakeCircle(zAxis, 100.0);
    Handle(AIS_Circle) shape = new AIS_Circle(circle);

    _aisContext()->Display(shape, false);
}


void DrawShapes_Viewport::DrawAxis()
{
    Handle(AIS_Axis) xAxis = new AIS_Axis(gp::OX(), 500.0);
    Handle(AIS_Axis) yAxis = new AIS_Axis(gp::OY(), 500.0);
    Handle(AIS_Axis) zAxis = new AIS_Axis(gp::OZ(), 500.0);

    _aisContext()->Display(xAxis, false);
    _aisContext()->Display(yAxis, false);
    _aisContext()->Display(zAxis, false);
}

void DrawShapes_Viewport::DrawPoint()
{
    for (int i = 0; i < 10; i++) {
        Handle(Geom_Point) point = new Geom_CartesianPoint(i * 100, 0, 0);
        Handle(AIS_Point) shape = new AIS_Point(point);

        _aisContext()->Display(shape, false);
    }
}

void DrawShapes_Viewport::DrawText()
{
    Handle(AIS_TextLabel) text = new AIS_TextLabel();
    text->SetText("AIS_TextLabel");
    
    _aisContext()->Display(text, false);
}

void DrawShapes_Viewport::DrawPlane()
{
    gp_Pnt origin = gp_Pnt();
    gp_Dir normal = gp::DZ();
    Handle(Geom_Plane) plane = GC_MakePlane(origin, normal);
    Handle(AIS_Plane) shape = new AIS_Plane(plane);

    _aisContext()->Display(shape, false);
}

void DrawShapes_Viewport::DrawBox()
{
    TopoDS_Shape box = BRepPrimAPI_MakeBox(100.0, 100.0, 100.0);

    Handle(AIS_Shape) shape = new AIS_Shape(box);
    shape->SetDisplayMode(1);

    _aisContext()->Display(shape, false);
}

void DrawShapes_Viewport::DrawCyliner()
{
    gp_Ax2 dir = gp::XOY();
    TopoDS_Shape box = BRepPrimAPI_MakeCylinder(dir, 100.0, 200.0);

    Handle(AIS_Shape) shape = new AIS_Shape(box);
    shape->SetDisplayMode(1);

    _aisContext()->Display(shape, false);
}


