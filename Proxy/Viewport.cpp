#include "Viewport.h"

#include <WNT_Window.hxx>

bool Viewport::Initialize(System::IntPtr handle)
{
	// graphic driver
	Handle(Aspect_DisplayConnection) displayConnection;
	_graphicDriver() = new OpenGl_GraphicDriver(displayConnection);

	// viewer 
	_viewer() = new V3d_Viewer(_graphicDriver());

	// view
	auto wntWindow = new WNT_Window(reinterpret_cast<HWND>(handle.ToPointer())); // window
	_view() = _viewer()->CreateView();
	_view()->SetWindow(wntWindow);

	if (!wntWindow->IsMapped())
	{
		wntWindow->Map();
	}

	// interactive context
	_aisContext() = new AIS_InteractiveContext(_viewer());
	_aisContext()->UpdateCurrentViewer();

	// update view
	_view()->Redraw();
	_view()->MustBeResized();

	return false;
}

void Viewport::Update()
{
	_view()->Redraw();
}

void Viewport::SetBackgroudColor(System::Drawing::Color backgroundColor)
{
	if (_view().IsNull())
	{
		return;
	}

	_view()->SetBackgroundColor(Quantity_TOC_RGB,
		backgroundColor.R / 255.0,
		backgroundColor.G / 255.0,
		backgroundColor.B / 255.0);
}
