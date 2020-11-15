/**
 * \file TowerBomb.h
 *
 * \author Kali Densmore
 *
 * Bomb Tower class that self destructs and pops balloons within the radius of its 
 * explosion. The time until explosion is increased depending on the number of 
 * towers placed on the game. 
 */

#pragma once
#include "Item.h"
#include "Tower.h"
#include "TowerGame.h"
#include "XmlNode.h"
#include <memory>

 /** Class for Tower Bomb */
class CTowerBomb : public CTower
{
public:
    /** Overloaded Constructor
    * uses visitor to calculate time that each tower explodes
    * \param game The game this is a member of
    */
    CTowerBomb(CTowerGame* game);

    /// Default constructor (disabled)
    CTowerBomb() = delete;

    /// Copy constructor (disabled)
    CTowerBomb(const CTowerBomb&) = delete;

    /// Default destructor
    ~CTowerBomb();

    /** Accept a visitor
    * \param visitor The visitor we accept */
    virtual void Accept(CItemVisitor* visitor) override { visitor->VisitTowerBomb(this); }

    void Fire();

    /**
    *Handle updates in time of our tower
    *
    * \param elapsed Time elapsed since the class call
    */
    virtual void Update(double elapsed) override;

    /**
     * Check if 5 seconds have passed to refire
     *
     * \param elapsed Time elapsed since the class call
     */
    void CheckFire(double elapsed);

    virtual void Draw(Gdiplus::Graphics* graphics) override;
   
private:
    /// Time Factor for when the bomb will explode based on number of bomb towers in the game
    double mTimeTillFire = 3;

    /// true when bomb should explode
    bool mFire = false;

    /// length of time bomb should explode
    double mFiringTime = .25;

};

