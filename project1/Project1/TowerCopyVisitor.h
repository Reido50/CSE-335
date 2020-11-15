/**
 * \file TowerCopyVisitor.h
 *
 * \author Kali Densmore
 *
 * Visitor that determines if the tower can be copied. If the tower is on the palette, 
 * it can be copied and placed moved to an open tile. 
 */

#pragma once
#include "ItemVisitor.h"
#include <string>

using namespace std;

/** Concrete Visitor for Copying Towers */
class CTowerCopyVisitor : public CItemVisitor
{
public:
    void VisitTowerEight(CTowerEight* towerEight) override;

    void VisitTowerRing(CTowerRing* towerRing) override;

    void VisitTowerBomb(CTowerBomb* towerBomb) override;

    void VisitTowerCustom(CTowerCustom* towerCustom) override;

    /**
    * Gets tower button we hit
    * \returns string of tower type
    */
    std::string TowerButton() { return mTower; }

private:
    /// tower type
    std::string mTower = "";
};


