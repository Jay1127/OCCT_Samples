#include "AIS_Solid.h"

#include <StdPrs_ShadedShape.hxx>
#include <StdPrs_WFShape.hxx>

AIS_Solid::AIS_Solid(const TopoDS_Shape& shape) 
    : _shape(shape)
{
    
}

void AIS_Solid::Compute(const Handle(PrsMgr_PresentationManager)& thePrsMgr,
    const Handle(Prs3d_Presentation)& thePrs,
    const Standard_Integer theMode)
{
    if (theMode == 0) {
        StdPrs_ShadedShape::Add(thePrs, _shape, myDrawer);
    }
    else if (theMode == 1) {
        StdPrs_WFShape::Add(thePrs, _shape, myDrawer);
    }
    else if (theMode == 2) {
        StdPrs_ShadedShape::Add(thePrs, _shape, myDrawer);
        StdPrs_WFShape::Add(thePrs, _shape, myDrawer);
    }
}