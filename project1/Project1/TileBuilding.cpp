/**
 * \file TileBuilding.cpp
 *
 * \author Jonathan Lee
 */

#include "pch.h"
#include "TileBuilding.h"
#include <vector>

using namespace std;
using namespace Gdiplus;

/// Tile filename 
const std::wstring TileBuildingImageName = L"images/house1.png";

/**
 * Constructor for loading node from xml
 * \param node Node we are loading
 * \param towerGame game we are loading into
 */
CTileBuilding::CTileBuilding(std::shared_ptr<xmlnode::CXmlNode> node, CTowerGame* towerGame) : CTile(node, towerGame)
{
}

/**
 * Constructor
 * \param towerGame The tower game this is a member of
 */
CTileBuilding::CTileBuilding(CTowerGame* towerGame) : CTile(towerGame, TileBuildingImageName)
{
}

/**
 * Supporting constructor used in testing
 * \param towerGame Tower Game we are a member of
 * \param file File we want to load as image
 */
CTileBuilding::CTileBuilding(CTowerGame* towerGame, std::wstring file) : CTile(towerGame, file)
{
}

/**
 * Destructor
 */
CTileBuilding::~CTileBuilding()
{
}

/**
 * Verifies that tile can support a tower
 * \returns False
 */
bool CTileBuilding::CanPlace()
{
	return false;
}
