/**
 * \file RoadVisitor.h
 *
 * \author Jonathan Lee
 *
 * Base class to implement road visiting
 */

#pragma once
#include "ItemVisitor.h"
#include <map>
#include <memory>
#include "TileRoad.h"

 /** Concrete Visitor for Road Tiles */
class CRoadVisitor : public CItemVisitor
{
public:
    /// Destructor
    virtual ~CRoadVisitor() {}

    virtual void VisitRoad(CTileRoad* road) override;

    /// Handles getting adjacencies to road tiles
    void ProcessRoads();

    /// Gets starting tile of map
    /// \return CTileRoad* starting tile
    CTileRoad* GetStart() { return mStart; }

    CTileRoad* HitTest(int x, int y);

private:

    CTileRoad* GetAdjacent(CTileRoad* road, int dx, int dy);

    /// Map of tiles using pairs of locations
    std::map<std::pair<int, int>, CTileRoad* > mRoads;

    /// Starting tile of map
    CTileRoad* mStart = nullptr;
};

