/**
 * \file TileTrees.h
 *
 * \author Jonathan Lee
 *
 * Implements the tree tile base class
 */

#pragma once
#include "Tile.h"
#include "Item.h"
#include "XmlNode.h"
#include <memory>

 /** Tree Tiles for the towergame */
class CTileTrees : public CTile
{
public:
    /// Constructor for node loading
    CTileTrees(std::shared_ptr<xmlnode::CXmlNode> node, CTowerGame *towerGame);

    /// Constructor
    CTileTrees(CTowerGame* towerGame);

    /// Supporting constructor
    CTileTrees(CTowerGame* towerGame, std::wstring file);

    /// Default constructor
    CTileTrees() = delete;

    /// Copy constructor
    CTileTrees(const CTileTrees&) = delete;

    /// Destructor
    ~CTileTrees();

    /** Accept a visitor
    * \param visitor The visitor we accept */
    virtual void Accept(CItemVisitor* visitor) override { visitor->VisitTrees(this); }

    /// Determines if tile can have tower placed on it
    /// \returns True if tile can
    virtual bool CanPlace() override;
};

