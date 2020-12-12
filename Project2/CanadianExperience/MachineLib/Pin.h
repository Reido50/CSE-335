/**
 * \file Pin.h
 *
 * \author Reid Harry
 *
 * Represents a pin in the system
 */

#pragma once

#include "Component.h"
#include "Cable.h"

class CBasket;

/** Represents a pin in the system */
class CPin :
    public CComponent
{
public:
    CPin();
    /** \brief Copy constructor disabled */
    CPin(const CPin&) = delete;
    /** \brief Assignment operator disabled */
    void operator=(const CPin&) = delete;
    ~CPin();

    void Update(double elapsed);
    void SetCable(CCable* cable);
    void SetBasket(std::shared_ptr<CBasket> basket);
private:
    /// Cable the pin is attached to
    CCable* mCable = nullptr;

    /// Basket the pin holds up
    std::shared_ptr<CBasket> mBasket;
};

