/**
 * \file MachineActual.h
 *
 * \author Reid Harry
 *
 * Used to represent a machine in the system
 */

#pragma once

#include "Machine.h"
#include "Assembly.h"

/** Used to represent a machine in the system */
class CMachineActual :
    public CMachine
{
public:
    CMachineActual(int machine);
    /** \brief Default constructor disabled */
    CMachineActual() = delete;
    /** \brief Copy constructor disabled */
    CMachineActual(const CMachineActual&) = delete;
    /** \brief Assignment operator disabled */
    void operator=(const CMachineActual&) = delete;
    ~CMachineActual();

    void DrawMachine(Gdiplus::Graphics* graphics);
    void SetMachineFrame(int frame);
    void SetMachineNumber(int machine);
    int GetMachineNumber();
    void SetLocation(int x, int y);
private:
    /// Position of the machine relative to the drawing space
    Gdiplus::Point mPosition = Gdiplus::Point(0, 0);

    /// Current frame of the animation
    int mFrame = 0;

    /// Frame rate of the animation
    int mFrameRate = 30;

    /// Number machine currently represented
    int mNumber = 1;

    /// Assembly of the machine's components
    std::shared_ptr<CAssembly> mAssembly;
};

