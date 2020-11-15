/**
 * \file Balloon.h
 *
 * \author Reid Harry
 *
 * Class that represents the balloon enemies
 */

#pragma once

#include "Item.h"

using namespace std;

 /** Class that represents balloons */
class CBalloon : public CItem
{
public:
	/// Constructor
	CBalloon(CTowerGame* towerGame, double position, double speed, int health);

	/// Supporting constructor
	CBalloon(CTowerGame* towerGame, double position, double speed);

	/// Destructor
	virtual ~CBalloon();

	/// Default Constructor
	CBalloon() = delete;

	/// Copy Constructor
	CBalloon(const CBalloon&) = delete;

	/// Enum type of causes of death
	enum class DeathCause { Alive, End, Eight, Ring, Bomb, Frisbee };

	/**  Set the item position
	* \param p The position of the baloon
	*/
	void SetPosition(double p) { mPosition = p; }

	/// mPosition Gettter
	/// \returns The position of the ballon on the current road tile
	double GetPosition() { return mPosition; };

	/// mSpeed Gettter
	/// \returns The speed of the balloon in virtual pixels per second
	double GetSpeed() { return mSpeed; };

	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CItemVisitor* visitor) override { visitor->VisitBalloon(this); }

	/**  Handle updates for animation
	* \param elapsed The time since the last update
	*/
	void Update(double elapsed) override;

	/**  Sets the Cause of Death for the balloon to determine its point value
	* \param cause DeathCause that caused the balloon to be removed from game
	*/
	void SetDeathCause(DeathCause cause) { mDeathCause = cause; }

	/// Called when balloon is hit by a tower
	void HitBalloon(DeathCause cause);

	/// Gets balloons current health value
	/// \return int health
	int GetHealth() { return mHealth; }

	/// Gets balloons hit status
	/// \return true if balloon is in hit cooldown
	bool IsHit() { return mHit; }

	virtual bool GetToDelete() override;

private:
	/// Position of the balloon on the current road tile
	double mPosition;

	/// Speed of the balloon in virtual pixels per second
	double mSpeed;

	/// Cause of death for balloon. Determines score influence
	DeathCause mDeathCause = DeathCause::Alive;

	/// Current health of the balloon
	int mHealth;

	/// Based on health. Returns filename of balloon
	/// \return wstring file name
	std::wstring GetBalloonFilename();

	/** Sets balloon to be deleted
	* \param toDelete boolean to determine if the balloon is to be deleted
	*/
	virtual void SetToDelete(bool toDelete) override;

	/// Amount of invulnerbility the balloon has after a hit in seconds
	double mHitCooldown = 0.3;

	/// Default amount of time for cooldown in seconds. Used in reset
	double mHitCooldownBase = 0.3;

	/// If true, balloon takes no damage
	bool mHit = false;
};

