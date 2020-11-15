/**
 * \file ExplodingVisitor.cpp
 *
 * \author Noel Lefevre
 */

#include "pch.h"
#include "ExplodingVisitor.h"
#include "Balloon.h"
#include <vector>
#include <algorithm>

/**Visit a Balloon object
* 
* \param balloon Balloon we are visiting
*/
void CExplodingVisitor::VisitBalloon(CBalloon* balloon) 
{
	mBalloons.push_back(balloon);
}

/**Loops through each balloon
* if balloon is within explosion radius, deletes balloon
* 
* \param x X coordinate of tower
* \param y Y coordinate of tower
* \param rad Radius of the explosion
* \param towertype Type of tower that hits balloon
*/
void CExplodingVisitor::ExplodeBalloon(int x, int y, int rad, std::string towertype)
{

	for (auto item : mBalloons) //for each balloon in vector
	{
		if (item->IsHit())
		{
			continue;
		}

		int bx = item->GetX(); 
		int by = item->GetY();

		int lowx = x -24 - rad/2;
		int lowy = y - 24 - rad/2;
		int highx = x + 24 + rad/2;
		int highy = y + 24 + rad/2;

		if (bx >= lowx && bx <= highx)
		{
			if (by >= lowy && by <= highy)
			{
				CBalloon::DeathCause cause;

				/// if balloon is within explosion, delete
				if (towertype == "Ring") 
				{
					cause = CBalloon::DeathCause::Ring;
				}
				else if (towertype == "Bomb")
				{
					cause = CBalloon::DeathCause::Bomb;
				}
				else if (towertype == "Frisbee")
				{
					cause = CBalloon::DeathCause::Frisbee;
				}
				else
				{
					cause = CBalloon::DeathCause::Eight;
				}

				item->HitBalloon(cause);
			}
		}
	}
}
