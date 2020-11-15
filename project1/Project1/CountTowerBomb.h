/**
 * \file CountTowerBomb.h
 *
 * \author Noel Lefevre
 *
 * visits TowerBombs to increment count
 */

#pragma once
#include "ItemVisitor.h"

 /** Concrete Visitor for counting bomb towers */
class CCountTowerBomb : public CItemVisitor
{
public:
    /** Visit a CTowerBomb object
    * \param towerbomb TowerBomb we are visiting */
    void VisitTowerBomb(CTowerBomb* towerbomb) override;

    /**Get Count: number of towerbomb tiles
    * \return mCount Number of towerbomb tiles
    */
    virtual double GetCount() { return mCount+1; }

private:
    ///> count of towerbombs
    double mCount = 0;
};

