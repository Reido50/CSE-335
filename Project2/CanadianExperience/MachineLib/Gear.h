/**
 * \file Gear.h
 *
 * \author Reid Harry
 *
 * Represents a gear in the system
 */

#pragma once

#include "Component.h"

/** Represents a gear in the system*/
class CGear :
    public CComponent
{
public:
    CGear(double radius, int numTeeth);
    CGear() = delete;
    /** \brief Copy constructor disabled */
    CGear(const CGear&) = delete;
    /** \brief Assignment operator disabled */
    void operator=(const CGear&) = delete;
    ~CGear();

    void Update(double elapsed) override;
    void Rotate(double rotation) override;

    int GetNumTeeth() override;
private:
    /// Radius of the gear in pixels
    double mRadius = 1;
    /// Number of teeth the gear has
    int mNumTeeth = 0;
};

