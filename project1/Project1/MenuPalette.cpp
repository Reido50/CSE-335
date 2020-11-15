/**
 * \file MenuPalette.h
 *
 * \author
 *
 * Handles Palette on screen
 */

#include "pch.h"
#include "MenuPalette.h"
#include "towerEight.h"
#include "towerBomb.h"
#include "towerCustom.h"
#include "towerRing.h"
#include "Announcer.h"
#include "GoButton.h"

using namespace Gdiplus;
using namespace std;

/// Initial towers X location
const int InitialX = 1124;

/// Initial towerEight Y location
const int InitialY = 200;

/// Initial towerRing Y location
const int InitialRingY = 100;

/// Initial towerBomb Y location
const int InitialBombY = 300;

/// Initial towerCustom Y location
const int InitialCustomY = 400;

/// Initial score display y
const int InitialScoreY = 500;

/// Initial score display x
const int InitialScoreX = 1100;

/// Initial score display y
const int InitialButtonY = 800;

/**
 * Constructor
 * \param towerGame Tower Game we are a member of
 */
CMenuPalette::CMenuPalette(CTowerGame* towerGame) : CItem(towerGame, L"")
{
	auto game = GetTowerGame();

	auto towerEight = make_shared<CTowerEight>(game);
	towerEight->SetLocation(InitialX, InitialY);
	towerEight->PlaceOnPalette();
	game->AddItem(towerEight);

	auto towerRing = make_shared<CTowerRing>(game);
	towerRing->SetLocation(InitialX, InitialRingY);
	towerRing->PlaceOnPalette();
	game->AddItem(towerRing);

	auto towerBomb = make_shared<CTowerBomb>(game);
	towerBomb->SetLocation(InitialX, InitialBombY);
	towerBomb->PlaceOnPalette();
	game->AddItem(towerBomb);

	// Only adding Custom Tower on level 3
	if (game->GetCurrentLevel() == 3)
	{
		auto towerCustom = make_shared<CTowerCustom>(game);
		towerCustom->SetLocation(InitialX, InitialCustomY);
		towerCustom->PlaceOnPalette();
		game->AddItem(towerCustom);
	}

	auto display = UpdateScore();
	game->AddItem(display);
	mScoreAnnouncer = display;

	// Removed logic from palette. Moved into towergame::AddGoButton
	// and CAnnouncerBegin
}

/**
 * Desctructor
 */
CMenuPalette::~CMenuPalette()
{

}

/**
 * Draws the components of the palette
 * \param graphics Graphics system we are drawing in
 */
void CMenuPalette::Draw(Gdiplus::Graphics* graphics)
{
	mScoreAnnouncer->Draw(graphics);
}

/**
 * Updates the menu. Used to draw score and go button
 * \param elapsed Time passed since last update
 */
void CMenuPalette::Update(double elapsed)
{
	auto game = GetTowerGame();
	auto display = UpdateScore();

	mScoreAnnouncer->SetToDelete(true);

	game->AddItem(display);
	mScoreAnnouncer = display;
}

/**
 * Helper method. 
 * Updates score display in palette
 * \return shared ptr to new announcer instance
 */
std::shared_ptr<CAnnouncer> CMenuPalette::UpdateScore()
{
	auto score = GetTowerGame()->GetScore();
	auto display = make_shared<CAnnouncer>(GetTowerGame(), L"Score: " + std::to_wstring(score), 255, 255, 0);
	display->SetLocation(InitialScoreX, InitialScoreY);
	return display;
}

