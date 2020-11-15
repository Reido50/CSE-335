/**
 * \file TowerVisitor.cpp
 *
 * \author Kali Densmore
 */

#include "pch.h"
#include "TowerVisitor.h"
#include "Tower.h"
#include "TowerEight.h"
#include "TowerBomb.h"
#include "TowerCustom.h"
#include "TowerRing.h"
#include "GrassVisitor.h"
#include "TowerGame.h"
#include <vector>

/**
 * Constructor
 * \param towerGame Tower Game we are a member of
 */
CTowerVisitor::CTowerVisitor(CTowerGame* towerGame)
{
	mTowerGame = towerGame;
}

/**
 * Main logic for towers. Unlocking and relocking towers.
 * \param tower Tower we are computing
 */
void CTowerVisitor::VisitorLogic(CTower* tower)
{
	int x = tower->GetX();
	int y = tower->GetY();

	CGrassVisitor visitor;
	mTowerGame->Accept(&visitor);
	CTileGrass* grass = visitor.GetGrassTile(x, y);

	auto towerGrass = tower->GetGrass();

	if (towerGrass == nullptr && grass != nullptr && grass->CanPlace())
	{
		// Tower is not linked and grass exists and is open
		// We link tower to grass and lock grass
		tower->SetGrass(grass);
		grass->SetOpen(false);
		tower->SetPlaced(true);

		// Matching locations
		int x = grass->GetX();
		int y = grass->GetY();

		tower->SetLocation(x, y);
	}
	else if (grass != nullptr && !grass->CanPlace())
	{
		// Grass is locked
		// We delete this copied tower instance
		tower->SetToDelete(true);
	}
	else if (grass == nullptr && !tower->OnPalette())
	{
		// Not grass tile and tower is not on palette
		// We delete this copied tower instance
		tower->SetToDelete(true);
	}
}

/**
 * Tower eight visitor
 * \param towerEight tower we are visiting
 */
void CTowerVisitor::VisitTowerEight(CTowerEight* towerEight)
{
	if (!towerEight->HasPlaced())
	{
		VisitorLogic(towerEight);
	}

	mTowers.push_back(towerEight);
}

/**
 * Tower ring visitor
 * \param towerRing tower we are visiting
 */
void CTowerVisitor::VisitTowerRing(CTowerRing* towerRing)
{
	if (!towerRing->HasPlaced())
	{
		VisitorLogic(towerRing);
	}

	mTowers.push_back(towerRing);
}

/**
 * Tower bomb visitor
 * \param towerBomb tower we are visiting
 */
void CTowerVisitor::VisitTowerBomb(CTowerBomb* towerBomb)
{
	
	if (!towerBomb->HasPlaced())
	{
		VisitorLogic(towerBomb);
	}
	
	mTowers.push_back(towerBomb);
}

/**
 * Tower custom visitor
 * \param towerCustom tower we are visiting
 */
void CTowerVisitor::VisitTowerCustom(CTowerCustom* towerCustom)
{
	
	if (!towerCustom->HasPlaced())
	{
		VisitorLogic(towerCustom);
	}

	mTowers.push_back(towerCustom);
}

/**
 * Visitor hit test. Called in mouse down
 * Usage on vectors of size 1.
 * \param x X coord
 * \param y Y coord
 * \return bool true if tower in vector was hit. false otherwise*/
bool CTowerVisitor::HitTest(int x, int y)
{
	// If game is active we don't care
	if (mTowerGame->IsActive() || mTowers.size() != 1)
	{
		return false;
	}

	// Grabbing first item only
	auto tower = mTowers.front();

	// Check if hit and tower was placed on map
	if (tower->HitTest(x, y) && tower->HasPlaced())
	{
		// Get grass pointer of grabbed tower
		auto grass = tower->GetGrass();
		if (grass != nullptr)
		{
			// Remove pointer
			tower->SetGrass(nullptr);

			// Unlocking grass
			grass->SetOpen(true);

			// Unlocking tower
			tower->SetPlaced(false);
			return true;
		}
	}
	return false;
}
