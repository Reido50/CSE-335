/**
 * \file TowerVisitor.h
 *
 * \author Kali Densmore
 *
 * Visitor that sets the location of the tower
 * If the location is not suitable, the object is deleted
 */

#pragma once
#include "ItemVisitor.h"
#include "TowerGame.h"
#include "Tower.h"

 /** Concrete Visitor for Towers */
class CTowerVisitor : public CItemVisitor
{
public:
    CTowerVisitor(CTowerGame* towerGame);

    /// copy constructor (disabled)
    CTowerVisitor() = delete;

    void VisitTowerEight(CTowerEight* towerEight);

    void VisitTowerRing(CTowerRing* towerRing);

    void VisitTowerBomb(CTowerBomb* towerBomb);

    void VisitTowerCustom(CTowerCustom* towerCustom);

    bool HitTest(int x, int y);

    /** Calls hit test on single tower instance
    * \param x X coord
    * \param y Y coord
    * \return bool of if the tower was clicked on*/
    bool HitTest(double x, double y) { return HitTest((int)x, (int)y); }

private:
    /// all towers in the game
    std::vector<CTower*> mTowers;

    /// the Tower Game 
    CTowerGame* mTowerGame;

    /**
    * Main logic for towers. Unlocking and relocking towers.
    * \param tower Tower we are computing
    */
    void VisitorLogic(CTower* tower);
};

