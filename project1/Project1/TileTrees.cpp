/**
 * \file TileTrees.cpp
 *
 * \author Jonathan Lee
 */

#include "pch.h"
#include "TileTrees.h"

using namespace Gdiplus;

/// Tile filename 
const std::wstring TileTreesImageName = L"images/trees4.png";

/**
 * Constructor for node loading
 * \param node The node we are loading
 * \param towerGame Game we are loading the node into
 */
CTileTrees::CTileTrees(std::shared_ptr<xmlnode::CXmlNode> node, CTowerGame *towerGame) : CTile(node, towerGame)
{
}

/**
 * Constructor
 * \param towerGame The tower game this is a member of
 */
CTileTrees::CTileTrees(CTowerGame* towerGame) : CTile(towerGame, TileTreesImageName)
{
}

/**
 * Constructor
 * \param towerGame The tower game this is a member of
 * \param file File that holds this image to be loaded into the game
 */
CTileTrees::CTileTrees(CTowerGame* towerGame, std::wstring file) : CTile(towerGame, file)
{
}

/**
 * Destructor 
 */
CTileTrees::~CTileTrees()
{
}

/**
 * Verifies that tower can be placed on tile
 * \returns False
 */
bool CTileTrees::CanPlace()
{
	return false;
}
