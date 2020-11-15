/**
 * \file AnnouncerBegin.cpp
 *
 * \author Jonathan Lee
 */

#include "pch.h"
#include "AnnouncerBegin.h"
#include "Announcer.h"
#include "TowerGame.h"
#include <string>

/**
 * Constructor for announcer
 * \param towerGame TowerGame we are a member of
 */
CAnnouncerBegin::CAnnouncerBegin(CTowerGame* towerGame) : CAnnouncer(towerGame, L"", 255, 255, 0)
{
	mFontSize = 64;
}

//Destructor
CAnnouncerBegin::~CAnnouncerBegin()
{
}

/**
 * Constructs the proper string and draws on screen
 * \param graphics Graphics system we are drawing to
 */
void CAnnouncerBegin::Draw(Gdiplus::Graphics* graphics)
{
	auto game = GetTowerGame();
	int level = game->GetCurrentLevel();
	SetLocation(350, 400);

	// Locking the players grabs
	CTowerGame::MessageState state = CTowerGame::MessageState::Begin;
	game->SetMessageState(state);

	mMessage = L"Level " + std::to_wstring(level) + L" begin!";
	CAnnouncer::Draw(graphics);
}

/**
 * Handles updates of announcer
 * \param elapsed Time elapsed since the last call
 */
void CAnnouncerBegin::Update(double elapsed)
{
	mTimeTillDelete -= elapsed;
	if (mTimeTillDelete <= 0)
	{
		SetToDelete(true);
		auto game = GetTowerGame();

		CTowerGame::MessageState state = CTowerGame::MessageState::None;
		game->SetMessageState(state);

		// Once message is deleted we add go button to screen
		game->AddGoButton();
	}
}
