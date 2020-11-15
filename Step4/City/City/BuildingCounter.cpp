/**
 * \file BuildingCounter.cpp
 *
 * \author Reid Harry
 */

#include "pch.h"
#include "BuildingCounter.h"

/** Visit a CTleBuilding object
 * \param building Building we are visiting */
void CBuildingCounter::VisitBuilding(CTileBuilding* building)
{
	mNumBuildings++;
}