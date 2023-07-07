#pragma once

#ifndef AIS_CURVE_H
#define AIS_CURVE_H

#include <AIS_InteractiveObject.hxx>
#include <Geom_Curve.hxx>

/// <summary>
/// ais object for curve <para/>
/// https://dev.opencascade.org/doc/overview/html/tutorials__ais_object.html#intro
/// </summary>
class AIS_Curve : public AIS_InteractiveObject    
{
    /// <summary>
    /// DEFINE_STANDARD_RTTI_INLINE() macro will register the new class within the OCCT Run-Time Type Information (RTTI) system.
    /// This step is optional (you may skip it if you are not going to use methods like Standard_Transient::DynamicType() in application code), 
    /// but it is a common practice while subclassing OCCT classes.
    /// </summary>
    DEFINE_STANDARD_RTTI_INLINE(AIS_Curve, AIS_InteractiveObject)

public:
    AIS_Curve(const Handle(Geom_Curve)& curve);

    /// <summary>
    /// defining an object presentation
    /// </summary>
    virtual void Compute(const Handle(PrsMgr_PresentationManager)& thePrsMgr,
        const Handle(Prs3d_Presentation)& thePrs,
        const Standard_Integer theMode) override;

    /// <summary>
    /// defining a selectable (pickable) volume
    /// </summary>
    /// <param name="theSelection"></param>
    /// <param name="theMode"></param>
    virtual void ComputeSelection(const Handle(SelectMgr_Selection)& theSelection,
        const Standard_Integer theMode) override {}

private:
    Handle(Geom_Curve) _curve;
};

#endif