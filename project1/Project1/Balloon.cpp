 /**
 * \file Balloon.cpp
 *
 * \author Reid Harry
 */

#include "pch.h"
#include "Balloon.h"
#include "TowerGame.h"
#include "RoadVisitor.h"

#include <memory>

/// Red Balloon filename 
const std::wstring RedBalloonImageName = L"red-balloon.png";
/// Blue balloon filename
const std::wstring BlueBalloonImageName = L"blue-balloon.png";
/// Black balloon filename
const std::wstring BlackBalloonImageName = L"black-balloon.png";
/// Owen balloon filename
const std::wstring OwenBalloonImageName = L"owen.png";


/**overide of Item constructor to include position and speed
*\param towerGame game that is currently running
* \param speed Speed in which Balloon moves
* \param position Current position of balloon
* \param health 1-3 value of health. Determines color of balloon
*/
CBalloon::CBalloon(CTowerGame* towerGame, double position, double speed, int health) : CItem(towerGame, L"")
{
	mPosition = position;
	mSpeed = speed;
	mHealth = health;

	SetImage(GetBalloonFilename());
}

/**
 * Supporting constructor that ignores health difference
 * \param towerGame game that is currently running
 * \param position Current position of balloon
 * \param speed Speed of the balloon
 */
CBalloon::CBalloon(CTowerGame* towerGame, double position, double speed) : CItem(towerGame, L"")
{
	mPosition = position;
	mSpeed = speed;
	mHealth = 1;

	SetImage(GetBalloonFilename());
}

/// Destructor
CBalloon::~CBalloon()
{
}

/*Updates current time within game
*\param elasped Previous elapsed time during last update
*/
void CBalloon::Update(double elapsed)
{
	mPosition += (mSpeed/64.0) * elapsed;

	// If balloon was hit we update timer
	if (mHit)
	{
		mHitCooldown -= elapsed;
	}
	if (mHitCooldown <= 0)
	{
		mHitCooldown = mHitCooldownBase;
		mHit = false;
	}
}

/**
 * "Hits" balloon and reduces health
 * If health hits 0 it calls delete functions
 * \param cause DeathCause enum value of balloon
 */
void CBalloon::HitBalloon(DeathCause cause)
{
	// Balloon is hit protected. We don't care
	if (mHit)
	{
		return;
	}
	// Marking balloon as hit and updating graphic
	if (cause != DeathCause::End)
	{
		mHealth--;		
		mHit = true;
		SetImage(GetBalloonFilename());
	}
	// Balloon is dead or hit end of map
	if (mHealth <= 0 || cause == DeathCause::End)
	{
		mDeathCause = cause;
		SetToDelete(true);
	}
}

/**
 * Handles scoring on balloon removal 
 */
void CBalloon::SetToDelete(bool toDelete)
{	
	// Following checks should pass if balloon is alive
	auto game = GetTowerGame();
	if (mDeathCause == DeathCause::End)
	{
		game->DecreaseScore(mHealth);
	}
	else if (mDeathCause == DeathCause::Ring)
	{
		game->IncreaseScore(3);
	}
	else if (mDeathCause == DeathCause::Bomb)
	{
		game->IncreaseScore(3);
	}
	else if (mDeathCause == DeathCause::Eight)
	{
		game->IncreaseScore(10);
	}
	else if (mDeathCause == DeathCause::Frisbee)
	{
		game->IncreaseScore(5);
	}

	game->DecreaseBalloonCount();
	CItem::SetToDelete(toDelete);
}

/**
 * Gets if item needs to be removed in cleanup cycle
 * 
 * Override function. Handled scoring game by
 * being called in TowerGame::RemoveToDelete
 * 
 * \return bool True if item should be deleted
 */
bool CBalloon::GetToDelete()
{
	return CItem::GetToDelete();
}

/**
 * Selects image file name based on health
 * \return file name
 */
std::wstring CBalloon::GetBalloonFilename()
{
	if (mHealth > 3)
	{
		return OwenBalloonImageName;
	}
	else if (mHealth == 3)
	{
		return BlackBalloonImageName;
	}
	else if (mHealth == 2)
	{
		return BlueBalloonImageName;
	}
	else
	{
		return RedBalloonImageName;
	}
}