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

    void virtual Rotate(double rotation);
    void virtual Draw(Gdiplus::Graphics* graphics, Gdiplus::Point position);
    void virtual Update(double elapsed) = 0;
    void SetPosition(Gdiplus::Point position);
    void SetAssembly(CAssembly* assembly);
protected:
    /// Polygon the component represents
    std::shared_ptr<CPolygon> mPolygon;
private:
	/// Position of component in relation to Machine
	Gdiplus::Point mPosition = Gdiplus::Point(0, 0);
    /// Rotation of component in degrees
    double mRotation = 0;
    /// Assembly the component is associated with
    CAssembly* mAssembly;
};

