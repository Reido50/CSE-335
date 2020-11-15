/**
 * \file AnnouncerComplete.cpp
 *
 * \author Jonathan Lee
 */

#include "pch.h"
#include "AnnouncerComplete.h"
#include "Announcer.h"
#include "TowerGame.h"
#include <string>

/**
* Constructor for announcer
* \param towerGame TowerGame we are a member of
*/
CAnnouncerComplete::CAnnouncerComplete(CTowerGame* towerGame) :
	CAnnouncer(towerGame, L"", 255, 255, 0)
{
	mFontSize = 64;
}

//Destructor
CAnnouncerComplete::~CAnnouncerComplete()
{
}

/**
 * Constructs the proper string and draws on screen
 * \param graphics Graphics system we are drawing to
 */
void CAnnouncerComplete::Draw(Gdiplus::Graphics* graphics)
{
	auto game = GetTowerGame();
	SetLocation(350, 400);

	// Locking player grabs
	CTowerGame::MessageState state = CTowerGame::MessageState::End;
	game->SetMessageState(state);
	mMessage = L"Level Complete!";
	CAnnouncer::Draw(graphics);
}

/**
 * Handles updates of announcer
 * \param elapsed Time elapsed since the last call
 */
void CAnnouncerComplete::Update(double elapsed)
{
	mTimeTillDelete -= elapsed;
	if (mTimeTillDelete <= 0)
	{
		SetToDelete(true);
		auto game = GetTowerGame();

		CTowerGame::MessageState state = CTowerGame::MessageState::Progress;
		game->SetMessageState(state);
	}
}
