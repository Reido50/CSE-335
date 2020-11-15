/**
 * \file TowerCopyVisitor.cpp
 *
 * \author Kali Densmore
 */

#include "pch.h"
#include "TowerCopyVisitor.h"
#include "TowerEight.h"
#include "TowerRing.h"
#include "TowerBomb.h"
#include "TowerCustom.h"
#include "TowerGame.h"
#include <string>

using namespace Gdiplus;
using namespace std;


/**Visit a TowerEight object
* \param towerEight tower we are visiting
*/
void CTowerCopyVisitor::VisitTowerEight(CTowerEight* towerEight)
{
	if (towerEight->OnPalette())
		mTower = "eight";
}

/**Visit a TowerEight object
* \param towerRing tower we are visiting
*/
void CTowerCopyVisitor::VisitTowerRing(CTowerRing* towerRing)
{
	if (towerRing->OnPalette())
		mTower = "ring";
}

/**Visit a TowerBomb object
* \param towerBomb tower we are visiting
*/
void CTowerCopyVisitor::VisitTowerBomb(CTowerBomb* towerBomb)
{
	if (towerBomb->OnPalette())
		mTower = "bomb";
}

/**Visit a TowerEight object
* \param towerCustom tower we are visiting
*/
void CTowerCopyVisitor::VisitTowerCustom(CTowerCustom* towerCustom)
{
	if (towerCustom->OnPalette())
		mTower = "custom";
}
