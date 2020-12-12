/**
 * \file Winch.h
 *
 * \author Reid Harry
 *
 * Represents a winch in the system
 */

#pragma once

#include "Component.h"
#include "Cable.h"

/** Represents a winch in the system */
class CWinch :
    public CComponent
{
public:
    CWinch();
    /** \brief Copy constructor disabled */
    CWinch(const CWinch&) = delete;
    /** \brief Assignment operator disabled */
    void operator=(const CWinch&) = delete;
    ~CWinch();

    void Update(double elapsed) override;
    void Draw(Gdiplus::Graphics* graphics, Gdiplus::Point position) override;
    void SetRotation(double rotation) override;
    void SetOn(bool on);
    CCable* GetCable();
private:
    /// True if the winch is on
    bool mOn = true;
    /// Speed of the winch in pixels per rotation
    double mSpeed = 10.0;
    /// Cable for the winch
    CCable mCable;
};

