/**
 * \file Tile.h
 *
 * \author Jonathan Lee
 *
 * Implements base line functions for a tile on the game map.
 */

#pragma once
#include "Item.h"
#include "TowerGame.h"
#include "XmlNode.h"

 /** Base Class for all Tiles */
class CTile : public CItem
{
public:
    /// Node constructor
    CTile(std::shared_ptr<xmlnode::CXmlNode> node, CTowerGame* towerGame);

    /// Destructor
    virtual ~CTile();

    /// Default constructor
    CTile() = delete;

    /// Copy constructor
    CTile(const CTile&) = delete;

    /// Determines if tile can have tower placed on it
    /// \returns True if tile can
    virtual bool CanPlace() = 0;

    virtual void Draw(Gdiplus::Graphics* graphics) override;

protected:
    /// Helper constructor
    CTile(CTowerGame* towerGame, const std::wstring& filename);
};

