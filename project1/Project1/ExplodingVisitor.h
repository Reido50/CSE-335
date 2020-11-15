/**
 * \file ExplodingVisitor.h
 *
 * \author Noel Lefevre
 *
 * visits TowerBombs to increment count
 */

#pragma once
#include <vector>
#include "ItemVisitor.h"
#include "Balloon.h"
#include "string.h"

/// Visitor class to delete balloons

class CExplodingVisitor : public CItemVisitor
{
public:
    /**Visit a Balloon object
    *
    * \param balloon Balloon we are visiting
    */
    void VisitBalloon(CBalloon* balloon) override;

    /**Loops through each balloon
    * if balloon is within explosion radius, deletes balloon
    *
    * \param x X coordinate of tower
    * \param y Y coordinate of tower
    * \param rad Radius of the explosion
    * \param towertype Type of tower that hits balloon
    */
    void ExplodeBalloon(int x, int y, int rad, std::string towertype);

    /**Loops through each balloon
    * if balloon is within explosion radius, deletes balloon
    *
    * \param x X coordinate of tower
    * \param y Y coordinate of tower
    * \param rad Radius of the explosion
    * \param towertype Type of tower that hits balloon
    */
    void ExplodeBalloon(double x, double y, int rad, std::string towertype) { ExplodeBalloon((int)x, (int)y, rad, towertype); }

private:
    ///> vector of pointers to balloons in game
    std::vector<CBalloon*> mBalloons;
};

