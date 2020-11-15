/**
 * \file TowerBomb.cpp
 *
 * \author Kali Densmore
 */

#include "pch.h"
#include "TowerBomb.h"
#include "CountTowerBomb.h"
#include "ItemVisitor.h"
#include "ExplodingVisitor.h"
#include "Item.h"

using namespace std;
using namespace Gdiplus;

/// Tower filename 
const wstring TowerBombImageName = L"images/tower-bomb.png";

/// Diameter of explosion
const int BombDiameter = 200;

/**
* Three seconds between each firing
*/
const double TimeBetweenShots = 3;

/** 
* Three seconds between each firing
*/
CTowerBomb::CTowerBomb(CTowerGame* game) : CTower(game, TowerBombImageName)
{

    if (!OnPalette())
    {
        CCountTowerBomb visitor;
        GetTowerGame()->Accept(&visitor);
        double num = visitor.GetCount();
        mTimeTillFire = num * 3 - 3; 
    }
    
    SetImage(L"../"+TowerBombImageName);

}

/**
*  Destructor
*/
CTowerBomb::~CTowerBomb()
{
}

/**
*Handle updates in time of our tower
*
* \param elapsed Time elapsed since the class call
*/
void CTowerBomb::Update(double elapsed)
{
    CTower::Update(elapsed);
    mFiringTime -= elapsed;
    CheckFire(elapsed);
}

/**
 * Check if 5 seconds have passed to refire
 *
 * \param elapsed Time elapsed since the class call
 */
void CTowerBomb::CheckFire(double elapsed)
{
    /// We only want to trigger timer
    /// If level is active
    if (GetTowerGame()->IsActive())
    {
        mTimeTillFire -= elapsed;
    }
    if (mTimeTillFire <= 0 && !OnPalette())
    {

        mTimeTillFire += TimeBetweenShots;
        
        CTowerBomb::Fire();
    }
}

/**
 * Overridden draw function to add expanding Bomb
 *
 * \param graphics Graphics for each item
 */
void CTowerBomb::Draw(Gdiplus::Graphics* graphics)
{
    CItem::Draw(graphics); ///< upcall to Draw

    if (mFire == true && !OnPalette())
    {
        double locx = GetX();
        double locy = GetY();
        double width = GetWidth();
        double height = GetHeight();

        /// find the middle of the image
        int x = (int)(locx - BombDiameter / 2 + width / 2);
        int y = (int)(locy - BombDiameter / 2 + height / 2);

        SolidBrush red(Color(128, 0, 0));
        graphics->FillEllipse(&red, x, y, BombDiameter, BombDiameter);

        /// Instantiate visitor and send to all balloons
        /// If within the diameter of the middle of the bomb tower at time of 
        /// explosion, the balloon will be deleted
        CExplodingVisitor visitor;
        GetTowerGame()->Accept(&visitor);
        visitor.ExplodeBalloon(locx, locy, BombDiameter, "Bomb");

        /// Will only fire once, then will be deleted
        if (mFiringTime <= 0)
        {
            mFire = false;
            SetToDelete(true);
        }

    }
}

/**
 * Resets variables for draw function when fired
 */
void CTowerBomb::Fire()
{
    mFire = true;
    mFiringTime = .25;
}