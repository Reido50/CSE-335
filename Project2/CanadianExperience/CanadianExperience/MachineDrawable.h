/**
 * \file MachineDrawable.h
 *
 * \author Reid Harry
 *
 * Used to draw a machine
 */

#pragma once

#include "Drawable.h"
#include "Machine.h"

/** Used to draw a machine */
class CMachineDrawable :
    public CDrawable
{
public:
    CMachineDrawable(const std::wstring& name, int machine);
    virtual ~CMachineDrawable();

    /** Default constructor disabled */
    CMachineDrawable() = delete;
    /** Copy constructor disabled */
    CMachineDrawable(const CMachineDrawable&) = delete;
    /** Assignment operator disabled */
    void operator=(const CMachineDrawable&) = delete;

    virtual void Draw(Gdiplus::Graphics* graphics) override;
    virtual bool HitTest(Gdiplus::Point pos) override;
    void SetScale(double scale);
private:
    /// The machine we are drawing
    std::shared_ptr<CMachine> mMachine;
    /// Scale of the machine size
    double mScale = 1.0;
};

