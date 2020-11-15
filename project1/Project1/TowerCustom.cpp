/**
 * \file TowerCustom.cpp
 *
 * \author Kali Densmore
 */

#include "pch.h"
#include "TowerCustom.h"
#include "Tower.h"
#include "Frisbee.h"
#include "ExplodingVisitor.h"

using namespace std;
using namespace Gdiplus;

/// Tower filename 
const wstring TowerCustomImageName = L"images/zeke-2.png";

/** Constructor
* \param game The game this is a member of
*/
CTowerCustom::CTowerCustom(CTowerGame* game) : CTower(game, TowerCustomImageName)
{
}

/**
*  Destructor
*/
CTowerCustom::~CTowerCustom()
{
}

/**Handle updates in time of our tower. If it is 
* time to fire, create frisbee object and move in 
* direction of the mouse. 
* \param elapsed Time elapsed since the class call
*/
void CTowerCustom::Update(double elapsed)
{
	CTower::Update(elapsed);
	if (GetTowerGame()->IsActive())
	{
		mTimeTilFire -= elapsed;
	}

	/// Check for fire.
	if (mTimeTilFire <= 0 && !CTower::OnPalette())
	{
		mTimeTilFire += mTimeBetweenShots;
		auto frisbee = make_shared<CFrisbee>(CItem::GetTowerGame(), mFrisbeeSpeed, mFrisbeeAngle);
		frisbee->SetLocation(GetX()+GetWidth()/2, GetY()+GetHeight()/2);
		CItem::GetTowerGame()->AddItem(frisbee);

	}
}
