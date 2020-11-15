/**
 * \file TileBuilding.h
 *
 * \author Jonathan Lee
 *
 * Implements tile building class.
 */

#pragma once
#include "Tile.h"
#include "Item.h"
#include <memory>
#include "XmlNode.h"

 /** Tile Building Class with CTile as its base */
class CTileBuilding : public CTile
{
public:
    /// Constructor for node loading
    CTileBuilding(std::shared_ptr<xmlnode::CXmlNode> node, CTowerGame *towerGame);

    /// Constructor
    CTileBuilding(CTowerGame* towerGame);

    CTileBuilding(CTowerGame* towerGame, std::wstring file);

    /// Default constructor
    CTileBuilding() = delete;

    /// Copy constructor
    CTileBuilding(const CTileBuilding&) = delete;

    /// Destructor
    ~CTileBuilding();

    /** Accept a visitor
    * \param visitor The visitor we accept */
    virtual void Accept(CItemVisitor* visitor) override { visitor->VisitBuilding(this); }

    /// Determines if tile can have tower placed on it
    /// \returns True if tile can
    virtual bool CanPlace() override;
};

