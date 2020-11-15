/**
 * \file TowerRing.cpp
 *
 * \author Kali Densmore
 */

#include "pch.h"
#include "TowerRing.h"
#include "ItemVisitor.h"
#include "ExplodingVisitor.h"
#include <vector>

using namespace std;
using namespace Gdiplus;

/// Tower filename 
const wstring TowerRingImageName = L"images/tower-rings.png";

/** Constructor
* \param game The game this is a member of
*/
CTowerRing::CTowerRing(CTowerGame* game) : CTower(game, TowerRingImageName)
{
}

/**
*  Destructor
*/
CTowerRing::~CTowerRing()
{
}

/**
 * Handle updates in time of our tower
 *
 * \param elapsed Time elapsed since the class call
 */
void CTowerRing::Update(double elapsed)
{
    CTower::Update(elapsed);
    mRadius = elapsed * mRate + mRadius;
    CheckFire(elapsed);

}

/**
 * Check if 5 seconds have passed to refire
 *
 * \param elapsed Time elapsed since the class call
 */
void CTowerRing::CheckFire(double elapsed)
{
    // We only want to reduce time if game is active
    if (GetTowerGame()->IsActive())
    {
        mTimeTillFire -= elapsed;
    }
    if (mTimeTillFire <= 0)
    {
        mTimeTillFire += mTimeBetweenShots;
        CTowerRing::Fire();
    }
}

/**
 * Overridden draw function to add expanding ring
 *
 * \param graphics Graphics for each item
 */
void CTowerRing::Draw(Gdiplus::Graphics* graphics)
{
    CItem::Draw(graphics);
    if (mFire == true && !OnPalette())
    {
        double locx = GetX();
        double locy = GetY();
        double width = GetWidth();
        double height = GetHeight();

        int radInt = (int)mRadius;
        int x = (int)(locx - radInt / 2 + width / 2);
        int y = (int)(locy - radInt / 2 + height / 2);

        Pen red(Color(128, 0, 0));
        graphics->DrawEllipse(&red, x, y, radInt, radInt);

        CExplodingVisitor visitor;
        GetTowerGame()->Accept(&visitor);
        visitor.ExplodeBalloon(locx, locy, radInt, "Ring");

        if (mRadius >= 200)
        {
            mFire = false;
        }
        
    }
}

/**
 * Resets variables for draw function when fired
 */
void CTowerRing::Fire()
{
    mFire = true;
    mRadius = 10.00;
}
