/**
 * \file BalloonSpawner.cpp
 *
 * \author Jonathan Lee
 */

#include "pch.h"
#include "BalloonSpawner.h"
#include "Balloon.h"
#include "TowerGame.h"

/**
 * Main constructor. Uses CItem base class to implement
 * updates and timing specific spawning
 * \param towerGame TowerGame we are a member of
 */
CBalloonSpawner::CBalloonSpawner(CTowerGame* towerGame) : CItem(towerGame, L"")
{
}

/**
 * Destructor
 */
CBalloonSpawner::~CBalloonSpawner()
{
}

/**
 * Main update call. 
 * Handles spawning balloons and timing
 */
void CBalloonSpawner::Update(double elapsed)
{
	auto game = GetTowerGame();
	int level = game->GetCurrentLevel();

	// If we have over 30 balloons we don't care.
	if ((level < 3 && mNumSpawned >= 30) || (level == 3 && mNumSpawned >= 45))
	{
		game->SetMessageState(CTowerGame::MessageState::None);
		SetToDelete(true);
		return;
	}

	// If last balloon we delay until final owen
	if (mNumSpawned == 44)
	{
		mOwenDelay -= elapsed;
	}
	if (mOwenDelay <= 0)
	{
		mOwenDelay = 30;
		SpawnBalloon();
	}

	// Defaulting if first balloon
	// Calculating distance in pixels between last balloon and spawn
	int calc;
	if (mLastSpawned == nullptr || mLastSpawned->GetToDelete())
	{
		// Checking if LastSpawned exists or if marked to delete
		// If marked to delete we ignore because it doesn't have
		// a valid x location.
		calc = 42;
	}
	else
	{
		int x1 = mLastSpawned->GetX();
		int x2 = game->GetStartX();
		calc = abs(x1 - x2);
	}

	// If distance is ~42 we spawn another
	if (calc >= 42 && mNumSpawned < 44)
	{
		SpawnBalloon();
	}
}

/**
 * Helper method
 * Adds balloon to field based on level and
 * number of spawned balloons.
 */
void CBalloonSpawner::SpawnBalloon()
{
	auto game = GetTowerGame();

	// Make sure state is Spawning on spawn
	game->SetMessageState(CTowerGame::MessageState::Spawning);
	game->SetActive();

	// Depending on level and num of balloons
	// we spawn different balloons
	std::shared_ptr<CBalloon> balloon = nullptr;
	if (game->GetCurrentLevel() != 3 || mNumSpawned <= 15)
	{
		// Levels 0-2 get normal red ballons
		// Level 3 first 15 balloons are red
		balloon = std::make_shared<CBalloon>(game, 0, 128);
	}
	else if (mNumSpawned == 44)
	{
		// Level 3 last balloon is custom owen balloon
		balloon = std::make_shared<CBalloon>(game, 0, 128, 15);
	}
	else
	{
		// Even numbered balloons > 15 are blue
		// Odd numbered balloons > 15 are black
		if (mNumSpawned % 2 == 0)
		{
			balloon = std::make_shared<CBalloon>(game, 0, 128, 2);
		}
		else
		{
			balloon = std::make_shared<CBalloon>(game, 0, 128, 3);
		}
	}

	// Setting last spawned and number logic
	mLastSpawned = balloon;

	game->AddBalloon(balloon);
	mNumSpawned++;
}
