/**
 * \file Dart.h
 *
 * \author Reid Harry
 *
 * Class that represents the darts CTowerEight shoots
 */

#pragma once
#include "Item.h"
#include "TowerEight.h"

/** Class that represents a dart */
class CDart : public CItem
{
public:
	/** Dart Constructor
	* \param towerGame The game that we draw darts in 
	* \param tower TowerEight that will shoot the darts
	* \param mSpeed Speed of the darts 
	* \param mAngle Angle of each dart as it shoots
	* \param mDistanceFromTower distance from the tower to determine deletion
	*/
	CDart(CTowerGame* towerGame, CTowerEight* tower, double mSpeed, double mAngle, double mDistanceFromTower);

	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CItemVisitor* visitor) override { visitor->VisitDart(this); }

	/** Gets the speed of the dart
	* \return double speed representation of dart */
	double GetSpeed() { return mSpeed; }
	/** Gets the distance traveled from the tower
	* \return double distance represesntaion of the distance between the dart and its tower8 */
	double GetDistanceFromTower() { return mDistanceFromTower; }
	/** Checks the angle of the dart
	* \return the angle the dart has been fired at */
	double GetAngle() { return mAngle; }

	/**  Handle updates for animation
	* \param elapsed The time since the last update
	*/
	virtual void Update(double elapsed) override;

	void Draw(Gdiplus::Graphics* graphics) override;

	/// Copy Constructor
	CDart(const CDart&) = delete;

	/// Destructor
	~CDart();

private:
	/// Speed of the dart in virtual pixels per second
	double mSpeed = 200;

	/// Distance of the dart from it's tower
	double mDistanceFromTower = 10;

	/// Angle of the dart
	double mAngle = 0;

	/// Pointer to the tower this dart belongs to
	CTowerEight* mTower = nullptr;

	/// Constant to covert radians to degrees.
	const double RtoD = 57.2957795;
};

