/**
 * \file TileGrass.h
 *
 * \author Jonathan Lee
 *
 * Implements grass tile set
 */

#pragma once
#include "Tile.h"
#include "XmlNode.h"

 /** Grass Tile that towers are placed on */
class CTileGrass : public CTile
{
public:
    /// Constructor for node loading
    CTileGrass(std::shared_ptr<xmlnode::CXmlNode> node, CTowerGame *towerGame);

    CTileGrass(CTowerGame* towerGame, std::wstring file);

    CTileGrass(CTowerGame* towerGame);

    /// Default constructor
    CTileGrass() = delete;

    /// Copy constructor
    CTileGrass(const CTileGrass&) = delete;

    /// Default destructor
    ~CTileGrass();

    /** Accept a visitor
    * \param visitor The visitor we accept */
    virtual void Accept(CItemVisitor* visitor) override { visitor->VisitGrass(this); }

    /// Determines if tile can have tower placed on it
    /// \returns True if tile can
    virtual bool CanPlace() override;

    /// Sets if tile is open for towers
    /// \param open If true, tile is open
    void SetOpen(bool open) { mOpenGrass = open;  }

private:
    /// determines if the grass is open or is occupied by tower
    bool mOpenGrass = true;
};

