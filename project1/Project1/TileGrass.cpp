/**
 * \file TileGrass.cpp
 *
 * \author Jonathan Lee
 */

#include "pch.h"
#include "TileGrass.h"

using namespace Gdiplus;

/// Tile filename
const std::wstring TileGrassImageName = L"images/grass1.png";

/**
 * Constructor for loading node from xml
 * \param node Node we are loading
 * \param towerGame game we are loading into
 */
CTileGrass::CTileGrass(std::shared_ptr < xmlnode::CXmlNode> node, CTowerGame* towerGame) : CTile(node, towerGame)
{
}

/**
 * Constructor
 * \param towerGame The tower game this is a member of
 * \param file File this Tile is loading from
 */
CTileGrass::CTileGrass(CTowerGame* towerGame, std::wstring file) : CTile(towerGame, file)
{
}

/**
 * Supporting constructor used in testing
 * \param towerGame Tower Game we are a member of
 */
CTileGrass::CTileGrass(CTowerGame* towerGame) : CTile(towerGame, TileGrassImageName)
{
}

/**
 * Destructor 
 */
CTileGrass::~CTileGrass()
{
}

/**
 * Verifies that tower can be placed on tile
 * \return True
 */
bool CTileGrass::CanPlace()
{
	return mOpenGrass;
}