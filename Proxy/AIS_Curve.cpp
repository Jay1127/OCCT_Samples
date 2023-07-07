#include "AIS_Curve.h"

#include <StdPrs_Curve.hxx>
#include <StdPrs_PoleCurve.hxx>
#include <Prs3d_LineAspect.hxx>
#include <GeomAdaptor_Curve.hxx>

AIS_Curve::AIS_Curve(const Handle(Geom_Curve)& curve)
    : _curve(curve)
{

}

void AIS_Curve::Compute(const Handle(PrsMgr_PresentationManager)& thePrsMgr,
    const Handle(Prs3d_Presentation)& thePrs,
    const Standard_Integer theMode) {

    GeomAdaptor_Curve adaptorCurve = GeomAdaptor_Curve(_curve);
    myDrawer->SetLineAspect(new Prs3d_LineAspect(Quantity_NOC_RED, Aspect_TOL_SOLID, 1.0));
    StdPrs_Curve::Add(thePrs, adaptorCurve, myDrawer);
}