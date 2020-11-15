/**
 * \file BuildingCounter.h
 *
 * \author Reid Harry
 *
 * Visitor that counts buildings
 */



#pragma once

#include "TileVisitor.h"

/** Visitor class for counting buildings
 * Visitor that counts each building in a city */
class CBuildingCounter : public CTileVisitor
{
public:
	void VisitBuilding(CTileBuilding* building);

	/** Get number of buildings
	 * \returns Number of buildings */
	int GetNumBuildings() const { return mNumBuildings; }

private:
	/// Building counter
	int mNumBuildings = 0;
};

