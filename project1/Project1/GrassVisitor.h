/**
 * \file GrassVisitor.h
 *
 * \author Kali Densmore
 *
 * Visitor that finds the grass tile that the tower is placed on
 * If it is occupied or it is not placed directly on the open grass
 * tile, then a nullpointer is returned. 
 */

#pragma once
#include "ItemVisitor.h"
#include "TileGrass.h"

/** Visitor for finding a grass tile that a tower can be placed on */
class CGrassVisitor : public CItemVisitor
{
public:

    void VisitGrass(CTileGrass* grass);

    CTileGrass* GetGrassTile(int x, int y);

private:
    /// Vector of all unoccupied CTileGrass objects
    std::vector<CTileGrass*> mGrassTiles;
};

