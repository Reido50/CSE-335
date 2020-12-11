/**
 * \file Mouse.h
 *
 * \author Reid Harry
 *
 * Represents a mouse in the system
 */

#pragma once

#include "Component.h"
#include "Shape.h"
#include "Motor.h"

/** Represents a mouse in the system */
class CMouse :
    public CComponent
{
public:
    CMouse();
    /** \brief Copy constructor disabled */
    CMouse(const CMouse&) = delete;
    /** \brief Assignment operator disabled */
    void operator=(const CMouse&) = delete;
    ~CMouse();

    void Update(double elapsed) override;

    void SetStart(Gdiplus::Point start);
    void SetSpeed(double speed);
    void SetCheese(std::shared_ptr<CShape> cheese);
    void AddMotor(std::shared_ptr<CMotor> motor);
private:
    /// Start point for the mouse
    Gdiplus::Point mStart = Gdiplus::Point(0, 0);

    /// Position of the mouse if it did not stop and eat the cheese
    int mVirtualPositionX = 0;

    /// Move speed of mouse in pixels per second
    double mMoveSpeed = 35.0;

    /// Cheese the mouse moves toward
    std::shared_ptr<CShape> mCheese;

    std::vector<std::shared_ptr<CMotor>> mMotors;
};

