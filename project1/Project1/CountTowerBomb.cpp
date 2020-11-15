/**
 * \file CountTowerBomb.cpp
 *
 * \author Noel Lefevre
 *
 * visits TowerBomb to increment count
 */

#include "pch.h"
#include "CountTowerBomb.h"
#include "TowerBomb.h"

/** Visit a CTowerBomb object
* \param towerbomb TowerBomb we are visiting */
void CCountTowerBomb::VisitTowerBomb(CTowerBomb* towerbomb)
{
	mCount++; //adds one to count
}
