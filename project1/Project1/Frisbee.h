/**
 * \file Frisbee.h
 *
 * \author Sarah Swann
 *
 * Class for a frisbee item
 */

#pragma once
#include "Item.h"

/** Class for a frisbee */
class CFrisbee : public CItem
{
public:
    /// Constructor
    CFrisbee(CTowerGame*, double speed, double angle);

    void Update(double elapsed) override;

    void Draw(Gdiplus::Graphics* graphics);

    /** Accept a visitor
    * \param visitor The visitor we accept */
    virtual void Accept(CItemVisitor* visitor) override { visitor->VisitFrisbee(this); }

private:
    /// Speed of the frisbee in pixels per second
    double mSpeed;

    /// Angular velocity of the frisbee in radians/second
    double mAngularVelocity = 32.0;

    /// Angle of the image
    double mImageAngle = 0.0;

    /// Angle of the movement in degrees
    double mAngle = 90;
};

