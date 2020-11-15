/**
 * \file TileRoad.cpp
 *
 * \author Jonathan Lee
 */

#include "pch.h"
#include "TileRoad.h"

#include <iostream>

using namespace std;
using namespace Gdiplus;

/// Tile filename 
const std::wstring TileRoadImageName = L"images/roadNW.png";

/**
 * Constructor for node loading
 * \param node The node we are loading
 * \param towerGame The tower game we are a member of
 */
CTileRoad::CTileRoad(std::shared_ptr<xmlnode::CXmlNode> node, CTowerGame* towerGame) : CTile(node, towerGame)
{
	mType = node->GetAttributeValue(L"type", L"");
}

/**
 * Constructor
 * \param towerGame The tower game this tile is a part of
 * \param file the File we are loading the Road image from 
 */
CTileRoad::CTileRoad(CTowerGame* towerGame, std::wstring file) : CTile(towerGame, file)
{
}

/**
 * Supporting constructor used in testing
 * \param towerGame Tower Game we are a member of
 */
CTileRoad::CTileRoad(CTowerGame* towerGame) : CTile(towerGame, TileRoadImageName)
{
}

/**
 * Destructor
 */
CTileRoad::~CTileRoad()
{
}

/**
 * Checks if this road tile has a road tile neighbor
 * \returns true if has neighbor, false otherwise
 */
bool CTileRoad::HasNeighbor()
{
	if (mNorth == nullptr && mSouth == nullptr && mEast == nullptr && mWest == nullptr)
	{
		return false;
	}
	return true;
}

/**
 * Verifies that tile can support tower
 * \returns False
 */
bool CTileRoad::CanPlace()
{
	return false;
}

/**
 * Adds a balloon to the Road tile
 * \param balloon Shared pointer to the CBalloon to be added
 */
void CTileRoad::AddBalloon(std::shared_ptr<CBalloon> balloon)
{
	mBalloons.push_back(balloon);

	double balloonX = balloon->GetX();
	double balloonY = balloon->GetY();

	GetTowerGame()->ConvertToVirtualPixels(balloonX, balloonY);

	double roadX = GetX();
	double roadY = GetY();

	GetTowerGame()->ConvertToVirtualPixels(roadX, roadY);

	// Logic for setting the direction of the tile
	if (mIsStart)			// Balloon was added to the starting point
	{
		// The start tile is always backward (starting at W, going E)
		mIsForward = false;
	}
	else if (balloonX > roadX)	// Balloon entered from the East
	{
		// From this direction NE and SE
		// tiles will need to be marked as not forward
		if (mType[1] == 'E')
		{
			mIsForward = false;
		}
	}
	else if (balloonX < roadX)	// Balloon entered from the West
	{
		// From this direction all tiles
		// will need to be marked as not forward
		mIsForward = false;
	}
	else if (balloonY < roadY)	// Balloon entered from the north
	{
		// From this direction no tiles
		// will need to be marked as not forward
	}
	else if (balloonY > roadY)	// Balloon entered from the south
	{
		// From this direction only NS
		// tiles will need to be marked as not forward
		if (mType[0] == 'N')
		{
			mIsForward = false;
		}
	}
}

/**
 * Update with time for animation purposes
 * \param elapsed Elapsed time since last OnPaint
 */
void CTileRoad::Update(double elapsed)
{
	auto y = 0;
	auto x = 0;
	double pos = 0;

	// Vector of iterators to erase from the mBalloons vector
	vector<vector<shared_ptr<CBalloon>>::iterator> toDelete;

	// Using an iterator for loop because we need to store the
	// iterators in the toDelete vector for erasing to happen
	for (auto balloon = mBalloons.begin(); balloon != mBalloons.end(); balloon++)
	{
		pos = (*balloon)->GetPosition();
		y = GetY();
		x = GetX();

		// Accounts for the balloon moving in the backward direction
		if (!mIsForward)
		{
			pos = (1 - pos);
		}

		// Logic for finding the new position of the balloon
		// depending on the type of tile and which half of
		// the path it is on
		if (pos < 0.5)
		{
			// First half of path in the forward direction
			// Second half of path in the backward direction
			if (mType[0] == 'E')
			{
				x = (int)(GetX() - GetWidth() / 2 + (1 - pos) * GetWidth());
			}
			else if (mType[0] == 'N')
			{
				y = (int)(GetY() - GetHeight() / 2 + pos * GetHeight());
			}
			else if (mType[0] == 'S')
			{
				y = (int)(GetY() - GetHeight() / 2 + (1 - pos) * GetHeight());
			}
		}
		else
		{
			// Second half of path in the forward direction
			// First half of path in the backward direction
			if (mType[1] == 'W')
			{
				x = (int)(GetX() - GetWidth() / 2 + (1 - pos) * GetWidth());
			}
			else if (mType[1] == 'E')
			{
				x = (int)(GetX() - GetWidth() / 2 + pos * GetWidth());
			}
			else if (mType[1] == 'S')
			{
				y = (int)(GetY() - GetHeight() / 2 + pos * GetHeight());
			}
		}

		(*balloon)->SetLocation(x, y);

		// Test if balloon is at the end of the current tile
		if ((*balloon)->GetPosition() > 1.0)
		{
			try
			{
				toDelete.push_back(balloon);
				TransferBalloon(*balloon);
			}
			catch (exception& e)
			{
				std::cout << e.what() << std::endl;
			}
		}
	}

	// Erase all balloons that were transfered to the next tile
	// Try block in situation where balloon transfers and gets
	// hit by tower at same time
	for (auto trash : toDelete)
	{
		try 
		{
			mBalloons.erase(trash);
		}
		catch (exception& e) 
		{
			std::cout << e.what() << std::endl;
		}
	}
}

/**
 * Transfers a balloon to the next road tile
 * \param balloon Shared pointer to the balloon to be transfered
 */
void CTileRoad::TransferBalloon(shared_ptr<CBalloon> balloon)
{
	int x = balloon->GetX();
	int y = balloon->GetY();

	// Reset the position of the balloon
	// If the position > 1.0, then it retains the progress it made
	balloon->SetPosition(balloon->GetPosition() - 1.0);

	// Logic for which directionional tile the balloon 
	// gets transfered to
	if (x > GetX() && mEast != nullptr)
	{
		mEast->AddBalloon(balloon);
	}
	else if (x < GetX() && mWest != nullptr)
	{
		mWest->AddBalloon(balloon);
	}
	else if (y > GetY() && mSouth != nullptr)
	{
		mSouth->AddBalloon(balloon);
	}
	else if (y < GetY() && mNorth != nullptr)
	{
		mNorth->AddBalloon(balloon);
	}
	else
	{
		CBalloon::DeathCause cause = CBalloon::DeathCause::End;
		balloon->HitBalloon(cause);
	}
}

/**
 * Given pointers, sets the neighboring road member variables
 * \param north North neighbor road
 * \param south South neighbor road
 * \param east East neighbor road
 * \param west West neighbor road
 */
void CTileRoad::SetNeighborRoads(CTileRoad* north, CTileRoad* south, CTileRoad* east, CTileRoad* west)
{
	mNorth = north;
	mSouth = south;
	mEast = east;
	mWest = west;
}
