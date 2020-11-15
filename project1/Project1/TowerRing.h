/**
 * \file TowerRing.h
 *
 * \author Kali Densmore
 *
 * Tower Ring class that shoots a ring to pop balloons
 */

#pragma once
#include "Item.h"
#include "Tower.h"
#include "TowerGame.h"
#include "XmlNode.h"
#include <memory>

 /** Tower Ring Class with CTower as base class */
class CTowerRing : public CTower
{
public:
    /// constructor of the TowerRing Item
    CTowerRing(CTowerGame* game);

    ///  Default constructor (disabled)
    CTowerRing() = delete;

    ///  Copy constructor (disabled)
    CTowerRing(const CTowerRing&) = delete;

    /// Default destructor
    ~CTowerRing();

    /** Accept a visitor
    * \param visitor The visitor we accept */
    virtual void Accept(CItemVisitor* visitor) override { visitor->VisitTowerRing(this); }
    
    void Fire();

    /**
    * Handle updates in time of our tower
    * \param elapsed Time elapsed since the class call
    */
    virtual void Update(double elapsed) override;

    /**
    * Check if 5 seconds have passed to refire
    * \param elapsed Time elapsed since the class call
    */
    void CheckFire(double elapsed);

    virtual void Draw(Gdiplus::Graphics* graphics) override;

private:
    /// Time Factor for when the bomb will explode based on number of bomb towers in the game
    double mTimeTillFire = 5;

    /// Add 5 seconds back after fire
    double mTimeBetweenShots = 5;

    /// bool to determine if it is time to fire the ring
    bool mFire = false;

    /// Radius of the ring that is fired
    double mRadius = 5;

    /// speed of the ring expanding
    double mRate = 350;
};



