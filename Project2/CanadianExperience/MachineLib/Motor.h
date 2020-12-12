/**
 * \file Motor.h
 *
 * \author Reid Harry
 *
 * Represents a motor in the system
 */

#pragma once

#include "Component.h"
#include "Polygon.h"

/** Represents a motor in the system */
class CMotor :
    public CComponent
{
public:
    CMotor();
    /** \brief Copy constructor disabled */
    CMotor(const CMotor&) = delete;
    /** \brief Assignment operator disabled */
    void operator=(const CMotor&) = delete;
    ~CMotor();

    void Update(double elapsed) override;
    void Draw(Gdiplus::Graphics* graphics, Gdiplus::Point position) override;

    void SetRotationSpeed(double rot);
    void SetOn(bool on);
    std::shared_ptr<CPolygon> GetBody();
private:
    /// True if the motor is running
    bool mOn = false;

    /// Speed of the motors rotation in rotations per second
    double mRotationSpeed = 0;

    /// Square body of the motor
    std::shared_ptr<CPolygon> mBody;
};

