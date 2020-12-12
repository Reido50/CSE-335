/**
 * \file Basket.h
 *
 * \author Reid Harry
 *
 * Represents the basket in the system
 */

#pragma once

#include "Component.h"
#include "Pin.h"

/** Represents the basket in the system*/
class CBasket :
    public CComponent
{
public:
    CBasket();
    /** \brief Copy constructor disabled */
    CBasket(const CBasket&) = delete;
    /** \brief Assignment operator disabled */
    void operator=(const CBasket&) = delete;
    ~CBasket();

    void Update(double elapsed) override;

    void SetStart(Gdiplus::Point start);
    void SetSpeed(double speed);
    void SetPin(std::shared_ptr<CPin> pin);
private:
    /// Start position of the basket
    Gdiplus::Point mStart = Gdiplus::Point(0, -464);

    /// End position of the basket
    Gdiplus::Point mEnd = Gdiplus::Point(0, -200);

    /// Speed of the basket falling in pixels per second
    double mFallSpeed = 100;

    /// Y value of the basket if it did not stop
    double mVirtualPositionY = -464;

    /// Pin the basket is held up by
    std::shared_ptr<CPin> mPin;
};

