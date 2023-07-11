#include "CameraController_Viewport.h"

#include <WNT_Window.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <AIS_Shape.hxx>
#include <AIS_ViewController.hxx>

void CameraController_Viewport::Initialize(System::IntPtr handle)
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

    // set viewcube
    _viewCube() = new AIS_ViewCube();    
    _aisContext()->Display(_viewCube(), false);

    // update view
    _view()->Redraw();
    _view()->MustBeResized();
}

void CameraController_Viewport::Redraw()
{
    _view()->Redraw();
}

void CameraController_Viewport::UpdateResized()
{
    _view()->Window()->DoResize();
    _view()->MustBeResized();
    _view()->Invalidate();

    int width, height;
    _view()->Window()->Size(width, height);    
}

void CameraController_Viewport::MakeModel()
{
    gp_Ax2 dir = gp::XOY();
    TopoDS_Shape cylinder = BRepPrimAPI_MakeCylinder(dir, 100.0, 200.0);
    Handle(AIS_Shape) shape = new AIS_Shape(cylinder);
    shape->SetDisplayMode(1);
    _aisContext()->Display(shape, false);

    gp_Pnt corner1 = gp_Pnt(50, 50, 50);
    gp_Pnt corner2 = gp_Pnt(200, 200, 200);
    TopoDS_Shape box = BRepPrimAPI_MakeBox(corner1, corner2);
    shape = new AIS_Shape(box);
    shape->SetDisplayMode(1);
    _aisContext()->Display(shape, false);

    _view()->FitAll();
}

void CameraController_Viewport::Pan(int deltaX, int deltaY)
{
    _view()->Pan(deltaX, deltaY);
}

void CameraController_Viewport::Rotate(int x, int y)
{
    _view()->Rotation(x, y);
}

void CameraController_Viewport::Zoom(int x, int y, double delta)
{
    int width, height;
    _view()->Window()->Size(width, height);
    int x1 = x + width * delta / 10000.0;
    int y1 = y + height * delta / 10000.0;
    
    _view()->StartZoomAtPoint(x, y);
    _view()->ZoomAtPoint(x, y, x1, y1);
}

void CameraController_Viewport::StartRotation(int x, int y)
{
    _view()->StartRotation(x, y);
}

void CameraController_Viewport::MoveTo(int x, int y)
{
    _aisContext()->MoveTo(x, y, _view(), true);
}

void CameraController_Viewport::SetOrthogonalProjection()
{
    _view()->Camera()->SetProjectionType(Graphic3d_Camera::Projection_Orthographic);
}

void CameraController_Viewport::SetPerspectiveProjection()
{
    _view()->Camera()->SetProjectionType(Graphic3d_Camera::Projection_Perspective);
}

void CameraController_Viewport::SetTopView()
{
    _view()->SetProj(V3d_TypeOfOrientation::V3d_Zpos);
}

void CameraController_Viewport::SetBottomView()
{
    _view()->SetProj(V3d_TypeOfOrientation::V3d_Zneg);
}

void CameraController_Viewport::SetFrontView()
{
    _view()->SetProj(V3d_TypeOfOrientation::V3d_Yneg);
}

void CameraController_Viewport::SetRearView()
{
    _view()->SetProj(V3d_TypeOfOrientation::V3d_Ypos);
}

void CameraController_Viewport::SetLeftView()
{
    _view()->SetProj(V3d_TypeOfOrientation::V3d_Xneg);
}

void CameraController_Viewport::SetRightView()
{
    _view()->SetProj(V3d_TypeOfOrientation::V3d_Xpos);
}

void CameraController_Viewport::ZoomFit()
{
    _view()->FitAll();
}
