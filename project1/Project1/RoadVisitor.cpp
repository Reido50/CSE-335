/**
 * \file RoadVisitor.cpp
 *
 * \author Jonathan Lee
 */

#include "pch.h"
#include "RoadVisitor.h"
#include "TileRoad.h"

 /**
  * Visits road and adds to road vector
  * Also detects which road is the start
  * \param road Road tile we are visiting
  */
void CRoadVisitor::VisitRoad(CTileRoad* road)
{
	mRoads[std::pair<int, int>(road->GetX() / 64,
		road->GetY() / 64)] = road;
	if (road->IsStart())
	{
		mStart = road;
	}
}

/**
 * Processes road tiles and assigns necessary direction pointers
 */
void CRoadVisitor::ProcessRoads()
{
	for (const auto& any : mRoads)
	{
		auto road = any.second;

		auto north = GetAdjacent(road, 0, -1);
		auto east = GetAdjacent(road, 1, 0);
		auto south = GetAdjacent(road, 0, 1);
		auto west = GetAdjacent(road, -1, 0);

		road->SetNeighborRoads(north, south, east, west);
	}
}

/**
 * Helper function. Searches for adjacent road tiles to
 * given road tile.
 *
 * \param road Road tile we use as base
 * \param dx Directional left/right, -1=left, 1=right
 * \param dy Directional up/down, -1=up, 1=down
 * \returns CTileRoad pointer to adjacent tile
 */
CTileRoad* CRoadVisitor::GetAdjacent(CTileRoad* road, int dx, int dy)
{
	int atX = road->GetX() / 64 + dx;
	int atY = road->GetY() / 64 + dy;

	auto adj = mRoads.find(std::pair<int, int>(atX, atY));
	if (adj != mRoads.end())
	{
		return adj->second;
	}
	return nullptr;
}

/**
 * Iterates over all roads on map
 * \param x X coord
 * \param y Y coord
 * \return TileRoad pointer if hit, nullptr if none
 */
CTileRoad* CRoadVisitor::HitTest(int x, int y)
{
	for (const auto& item : mRoads)
	{
		if (item.second->HitTest(x, y))
		{
			return item.second;
		}
	}
	return nullptr;
}
