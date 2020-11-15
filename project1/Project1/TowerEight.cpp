/**
 * \file TowerEight.cpp
 *
 * \author Kali Densmore
 */

#include "pch.h"
#include "TowerEight.h"
#include <string>

using namespace std;
using namespace Gdiplus;

/// Tower filename 
const wstring TowerEightImageName = L"images/tower8.png";

/// 5 seconds default between each fire
const double TimeBetweenShots = 5;

/** Constructor
* \param game The game this is a member of
*/
CTowerEight::CTowerEight(CTowerGame* game) : CTower(game, TowerEightImageName)
{
}

/**
*  Destructor
*/
CTowerEight::~CTowerEight()
{
}

/**
 * Handle updates in time of our towers
 *
 * This is called before we draw and allows us to
 * fire from the towers.
 * \param elapsed Time elapsed since the class call
 */
void CTowerEight::Update(double elapsed)
{
    if (GetTowerGame()->IsActive())
    {
        mTimeTillFire -= elapsed;
    }
    if (mTimeTillFire <= 0 && !CTower::OnPalette())
    {
        Fire();
        mTimeTillFire += TimeBetweenShots;
    }

    ClearDarts();

    for (auto dart : mDarts)
    {
        dart->Update(elapsed);
    }
}


/**
 * Overridden draw function to add eight darts to game
 *
 * \param graphics Graphics for each item
 */
void CTowerEight::Draw(Gdiplus::Graphics* graphics)
{
    CItem::Draw(graphics);

    for (auto dart : mDarts)
    {
        if (dart->GetToDelete())
        {
            continue;
        }
        dart->Draw(graphics);
    }
}


/**
 * When called creates 8 dart objects and adds them to a vector
 */
void CTowerEight::Fire() 
{
    for (int i = 0; i < 8; i++)
    {
        auto dart = make_shared<CDart>(CItem::GetTowerGame(), this, 100, (3.14159/4.0)*i, 10);
        mDarts.push_back(dart);
    }

}

/**
 * Helper function
 * Clears dart vector of all darts marked to be deleted
 */
void CTowerEight::ClearDarts()
{
    mDarts.erase(
        std::remove_if(mDarts.begin(), mDarts.end(),
            [&](std::shared_ptr<CItem> item) { return item->GetToDelete(); }),
        mDarts.end());
}
