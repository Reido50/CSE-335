/**
 * \file GoButton.cpp
 *
 * \author Jonathan Lee
 */

#include "pch.h"
#include "GoButton.h"
#include "TowerGame.h"
#include <string>

using namespace std;
using namespace Gdiplus;

/// Tower filename 
const wstring ButtonImageName = L"images/button-go.png";

/** Constructor
* \param game The game this is a member of
*/
CGoButton::CGoButton(CTowerGame* game) : CItem(game, ButtonImageName)
{
}

/**
*  Destructor
*/
CGoButton::~CGoButton()
{
}

/**
 * Hit test for Go Button
 * \param x X value of the hit
 * \param y Y value of the hit
 * \returns bool True if the hit was on the object
 */
bool CGoButton::HitTest(int x, int y)
{
    double width = mImage->GetWidth();
    double height = mImage->GetHeight();

	bool hit = (x >= GetX() && x <= (GetX() + width) && y >= GetY() && y <= (GetY() + height));
	if (hit)
	{
		GetTowerGame()->StartLevel();
		SetToDelete(true);
	}
	return hit;
}