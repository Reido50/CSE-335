/**
 * \file Component.h
 *
 * \author Reid Harry
 *
 * Represents a part of the machine
 */

#pragma once

#include "Polygon.h"

class CAssembly;

/** Represents a part of the machine */
class CComponent
{
public:
    CComponent();
    /** \brief Copy constructor disabled */
    CComponent(const CComponent&) = delete;
    /** \brief Assignment operator disabled */
    void operator=(const CComponent&) = delete;

    void virtual SetRotation(double rotation);
    void virtual Draw(Gdiplus::Graphics* graphics, Gdiplus::Point position);
    /**
    * Called every frame before draw
    * \param elapsed Time in seconds since last update
    */
    void virtual Update(double elapsed) = 0;
    void SetPosition(Gdiplus::Point position);
    void SetAssembly(CAssembly* assembly);
    Gdiplus::Point GetPosition();
    std::shared_ptr<CPolygon> GetPolygon();
    void AddSink(std::shared_ptr<CComponent> sink);
    void SetSource(std::shared_ptr<CComponent> source);
    int virtual GetNumTeeth();
    bool virtual IsStacked();
    double GetRotation();
protected:
    /// Polygon the component represents
    std::shared_ptr<CPolygon> mPolygon;
    /// Source of rotation for this component
    CComponent* mSource = nullptr;
    /// Sinks of rotation for this component
    std::vector<CComponent*> mSinks;
    /// Rotation of component
    double mRotation = 0;
private:
    /// Position of component in relation to Machine
    Gdiplus::Point mPosition = Gdiplus::Point(0, 0);
    /// Assembly the component is associated with
    CAssembly* mAssembly;
};

