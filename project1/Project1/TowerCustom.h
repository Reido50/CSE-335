/**
 * \file TowerCustom.h
 *
 * \author Kali Densmore
 *
 * Custom Tower class that represents Zeke the wonderdog for MSU. Zeke shoots frisbees at the 
 * balloons in the direction that the mouse is at on the screen. If the balloon is popped 
 * by one of zeke's frisbees, 5 points is added to the score. He is only available once the player 
 * reaches level 3. 
 */

#pragma once
#include "Item.h"
#include "Tower.h"
#include "TowerGame.h"
#include "XmlNode.h"
#include <memory>

 /** Custom Tower Class */
class CTowerCustom : public CTower
{
public:

    CTowerCustom(CTowerGame* game);

    ///  Default constructor (disabled)
    CTowerCustom() = delete;

    ///  Copy constructor (disabled)
    CTowerCustom(const CTowerCustom&) = delete;

    /// Default destructor
    ~CTowerCustom();

    /// Sets angle of frisbee thrown
    /// \param angle Angle we are setting
    void SetAngle(double angle) { mFrisbeeAngle = angle; }

    void Update(double elapsed) override;

    /** Accept a visitor
    * \param visitor The visitor we accept */
    virtual void Accept(CItemVisitor* visitor) override { visitor->VisitTowerCustom(this); }

private:
    /// Angle the tower will shoot the 
    /// next frisbee at in radians
    double mFrisbeeAngle = 90.0;

    /// Time Factor for when the tower will fire its frisbee toward the direction of the mouse. 
    double mTimeTilFire = 5.0;

    /// Add this back to the time when mTimeTillFire < 0. This will help with the roundoff error
    double mTimeBetweenShots = 5.0;

    /// speed of the frisbee
    double mFrisbeeSpeed = 200.0;
};

