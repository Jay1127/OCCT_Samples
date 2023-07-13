#include "BooleanOperation_Viewport.h"

#include <WNT_Window.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepAlgoAPI_Common.hxx>
#include <BRepAlgoAPI_Cut.hxx>

#include <BRepOffsetAPI_ThruSections.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>

#include <AIS_Shape.hxx>

void BooleanOperation_Viewport::Initialize(System::IntPtr handle)
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

    // make model(two boxes)
    MakeModel();
    _view()->FitAll();

    // update view
    _view()->Redraw();
    _view()->MustBeResized();
}

void BooleanOperation_Viewport::Redraw()
{
    _view()->Redraw();
}

void BooleanOperation_Viewport::UpdateResized()
{
    _view()->Window()->DoResize();
    _view()->MustBeResized();
    _view()->Invalidate();

    int width, height;
    _view()->Window()->Size(width, height);
}

void BooleanOperation_Viewport::Pan(int deltaX, int deltaY)
{
    _view()->Pan(deltaX, deltaY);
}

void BooleanOperation_Viewport::Rotate(int x, int y)
{
    _view()->Rotation(x, y);
}

void BooleanOperation_Viewport::Zoom(int x, int y, double delta)
{
    int width, height;
    _view()->Window()->Size(width, height);
    int x1 = x + width * delta / 10000.0;
    int y1 = y + height * delta / 10000.0;

    _view()->StartZoomAtPoint(x, y);
    _view()->ZoomAtPoint(x, y, x1, y1);
}

void BooleanOperation_Viewport::MakeModel()
{
    gp_Pnt corner1 = gp_Pnt(0, 0, 0);
    gp_Pnt corner2 = gp_Pnt(1000, 100, 100);
    TopoDS_Shape box1 = BRepPrimAPI_MakeBox(corner1, corner2);

    gp_Pnt corner3 = gp_Pnt(450, -500, 50);
    gp_Pnt corner4 = gp_Pnt(550, 500, 150);
    TopoDS_Shape box2 = BRepPrimAPI_MakeBox(corner3, corner4);

    Handle(AIS_Shape) boxShape1 = new AIS_Shape(box1);
    boxShape1->SetColor(Quantity_NOC_RED);
    boxShape1->SetDisplayMode(1);
    Handle(AIS_Shape) boxShape2 = new AIS_Shape(box2);
    boxShape2->SetColor(Quantity_NOC_BLUE);
    boxShape2->SetDisplayMode(1);

    _aisContext()->RemoveAll(false);
    _aisContext()->Display(boxShape1, false);
    _aisContext()->Display(boxShape2, false);

    Redraw();
}

void BooleanOperation_Viewport::Union()
{
    gp_Pnt corner1 = gp_Pnt(0, 0, 0);
    gp_Pnt corner2 = gp_Pnt(1000, 100, 100);
    TopoDS_Shape box1 = BRepPrimAPI_MakeBox(corner1, corner2);

    gp_Pnt corner3 = gp_Pnt(450, -500, 50);
    gp_Pnt corner4 = gp_Pnt(550, 500, 150);
    TopoDS_Shape box2 = BRepPrimAPI_MakeBox(corner3, corner4);

    TopoDS_Shape fuse = BRepAlgoAPI_Fuse(box1, box2);

    Handle(AIS_Shape) boxShape1 = new AIS_Shape(box1);
    boxShape1->SetColor(Quantity_NOC_RED);
    boxShape1->SetDisplayMode(0);
    Handle(AIS_Shape) boxShape2 = new AIS_Shape(box2);
    boxShape2->SetColor(Quantity_NOC_BLUE);
    boxShape2->SetDisplayMode(0);
    
    Handle(AIS_Shape) fuseShape = new AIS_Shape(fuse);
    fuseShape->SetDisplayMode(1);

    _aisContext()->RemoveAll(false);
    _aisContext()->Display(boxShape1, false);
    _aisContext()->Display(boxShape2, false);
    _aisContext()->Display(fuseShape, false);

    Redraw();
}

void BooleanOperation_Viewport::Difference()
{
    gp_Pnt corner1 = gp_Pnt(0, 0, 0);
    gp_Pnt corner2 = gp_Pnt(1000, 100, 100);
    TopoDS_Shape box1 = BRepPrimAPI_MakeBox(corner1, corner2);

    gp_Pnt corner3 = gp_Pnt(450, -500, 50);
    gp_Pnt corner4 = gp_Pnt(550, 500, 150);
    TopoDS_Shape box2 = BRepPrimAPI_MakeBox(corner3, corner4);

    TopoDS_Shape cut = BRepAlgoAPI_Cut(box1, box2);

    Handle(AIS_Shape) boxShape1 = new AIS_Shape(box1);
    boxShape1->SetColor(Quantity_NOC_RED);
    boxShape1->SetDisplayMode(0);
    Handle(AIS_Shape) boxShape2 = new AIS_Shape(box2);
    boxShape2->SetColor(Quantity_NOC_BLUE);
    boxShape2->SetDisplayMode(0);

    Handle(AIS_Shape) cutShape = new AIS_Shape(cut);
    cutShape->SetDisplayMode(1);

    _aisContext()->RemoveAll(false);
    _aisContext()->Display(boxShape1, false);
    _aisContext()->Display(boxShape2, false);
    _aisContext()->Display(cutShape, false);

    Redraw();
}

void BooleanOperation_Viewport::Intersection()
{
    gp_Pnt corner1 = gp_Pnt(0, 0, 0);
    gp_Pnt corner2 = gp_Pnt(1000, 100, 100);
    TopoDS_Shape box1 = BRepPrimAPI_MakeBox(corner1, corner2);

    gp_Pnt corner3 = gp_Pnt(450, -500, 50);
    gp_Pnt corner4 = gp_Pnt(550, 500, 150);
    TopoDS_Shape box2 = BRepPrimAPI_MakeBox(corner3, corner4);

    TopoDS_Shape common = BRepAlgoAPI_Common(box1, box2);

    Handle(AIS_Shape) boxShape1 = new AIS_Shape(box1);
    boxShape1->SetColor(Quantity_NOC_RED);
    boxShape1->SetDisplayMode(0);
    Handle(AIS_Shape) boxShape2 = new AIS_Shape(box2);
    boxShape2->SetColor(Quantity_NOC_BLUE);
    boxShape2->SetDisplayMode(0);

    Handle(AIS_Shape) commonShape = new AIS_Shape(common);
    commonShape->SetDisplayMode(1);

    _aisContext()->RemoveAll(false);
    _aisContext()->Display(boxShape1, false);
    _aisContext()->Display(boxShape2, false);
    _aisContext()->Display(commonShape, false);

    Redraw();
}

void BooleanOperation_Viewport::StartRotation(int x, int y)
{
    _view()->StartRotation(x, y);
}