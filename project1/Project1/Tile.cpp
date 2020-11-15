/**
 * \file Tile.cpp
 *
 * \author Jonathan Lee
 */

#include "pch.h"
#include "Tile.h"
#include "TowerGame.h"


/**
 * Constructor for node loading
 * \param node The node we are loading
 * \param towerGame The tower game we are a member of
 */
CTile::CTile(std::shared_ptr<xmlnode::CXmlNode> node, CTowerGame *towerGame) : CItem(node, towerGame)
{
}

/**
 * Constructor for testing purposes
 * \param towerGame The towerGame this item is a member of
 * \param filename Name of the file for the image of the tile
 */
CTile::CTile(CTowerGame *towerGame, const std::wstring& filename) : CItem(towerGame, filename)
{
}

/**
 * Destructor
 */
CTile::~CTile()
{
}

/**
 * Main tile drawing function
 * Draws tile into graphics instance
 * \param graphics Graphics instance we draw to
 */
void CTile::Draw(Gdiplus::Graphics* graphics)
{
	auto wid = (int)GetImageWidth();
	auto hit = (int)GetImageHeight();

	graphics->DrawImage(mImage.get(),
		(int)GetX(), (int)GetY(),
		wid + 1, hit + 1);
}