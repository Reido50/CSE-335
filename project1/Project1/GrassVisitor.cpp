/**
 * \file GrassVisitor.cpp
 *
 * \author Kali Densmore
 */

#include "pch.h"
#include "GrassVisitor.h"

/**
 * Visits all grass tiles and collects them in a vector
 * \param grass CTileGrass that is collected in a vector
 */
void CGrassVisitor::VisitGrass(CTileGrass* grass)
{
	mGrassTiles.push_back(grass);
}

/**
 * As the tower is being placed, this function will return the grass tile
 * to set the tower on top of
 * 
 * \param x X location the tower is located
 * \param y Y location the tower is located
 * \returns a CTileGrass tile of the tile underneath the tower
 * Will return nullptr if there is no grass tile beneath the tower
 */
CTileGrass* CGrassVisitor::GetGrassTile(int x, int y)
{
	for (auto item : mGrassTiles)
	{
		if (item->HitTest(x, y))
		{
			//item->SetOpen(false);
			return item;
		}

	}
	
	return nullptr;
}
