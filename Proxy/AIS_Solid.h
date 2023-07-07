#pragma once

#ifndef AIS_SOLID_H
#define AIS_SOLID_H

#include <AIS_InteractiveObject.hxx>
#include <TopoDS_Shape.hxx>

class AIS_Solid : public AIS_InteractiveObject
{
    /// <summary>
    /// DEFINE_STANDARD_RTTI_INLINE() macro will register the new class within the OCCT Run-Time Type Information (RTTI) system.
    /// This step is optional (you may skip it if you are not going to use methods like Standard_Transient::DynamicType() in application code), 
    /// but it is a common practice while subclassing OCCT classes.
    /// </summary>
    DEFINE_STANDARD_RTTI_INLINE(AIS_Solid, AIS_InteractiveObject)

public:
    AIS_Solid(const TopoDS_Shape& shape);

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
    TopoDS_Shape _shape;
};


#endif 