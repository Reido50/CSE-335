/**
 * \file TileRoad.h
 *
 * \author Jonathan Lee
 *
 * Implements functionality for the road tile class
 */

#pragma once
#include "Tile.h"
#include "Item.h"
#include <memory>
#include "Balloon.h"
#include <vector>
#include "XmlNode.h"

 /** Road Tiles for the balloons to travel on */
class CTileRoad : public CTile
{
public:
    /// Constructor for node loading
    CTileRoad(std::shared_ptr<xmlnode::CXmlNode> node, CTowerGame* towerGame);

    /// Constructor
    CTileRoad(CTowerGame* towerGame, std::wstring file);

    /// Supporting construtor
    CTileRoad(CTowerGame* towerGame);

    /// Default constructor
    CTileRoad() = delete;

    /// Copy constructor
    CTileRoad(const CTileRoad&) = delete;

    /// Destructor
    ~CTileRoad();

    /** Accept a visitor
    * \param visitor The visitor we accept */
    virtual void Accept(CItemVisitor* visitor) override { visitor->VisitRoad(this); }

    /// Checks if tile has neighboring roads
    /// \return True if has neighbors
    bool HasNeighbor();

    /// Determines if tile can have tower placed on it
    /// \returns True if tile can
    virtual bool CanPlace() override;

    /// Gets the type of road
    /// \returns mType
    std::wstring GetType() { return mType; }

    /// Sets the type of road
    /// \param type Type to set the road to
    void SetType(std::wstring type) { mType = type; }

    void AddBalloon(std::shared_ptr<CBalloon> balloon);

    void TransferBalloon(std::shared_ptr<CBalloon> balloon);

    virtual void Update(double elapsed) override;

    /// Gets IsStart member
    /// \return bool True if tile is start of map
    bool IsStart() { return mIsStart; }

    /**  Sets IsStart member
     * \param isStart boolead to determine if road is a start road tile
    */
    void SetIsStart(bool isStart) { mIsStart = isStart; }

    /// Sets neighboring road pointers
    void SetNeighborRoads(CTileRoad* north, CTileRoad* south, CTileRoad* east, CTileRoad* west);

private:
    /// Pointer to north tile
    CTileRoad* mNorth = nullptr;

    /// Pointer to south tile
    CTileRoad* mSouth = nullptr;

    /// Pointer to west tile
    CTileRoad* mWest = nullptr;

    /// Pointer to east tile
    CTileRoad* mEast = nullptr;

    /// Type of road tile
    std::wstring mType;

    /// Collection of balloons on this road tile
    std::vector<std::shared_ptr<CBalloon>> mBalloons;

    /// Determines if this EW road tile is beginning of map
    bool mIsStart = false;

    /// Determines if the road is forward
    /// Forward depends on the tile type
    /// EW: Starting at E, ending at W
    /// NS: Starting at N, ending at S
    /// NE: Starting at N, ending at E
    /// NW: Starting at N, ending at W
    /// SE: Starting at S, ending at E
    /// SW: Starting at S, ending at W
    bool mIsForward = true;
};

