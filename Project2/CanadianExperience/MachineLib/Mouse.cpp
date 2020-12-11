/**
 * \file Mouse.cpp
 *
 * \author Reid Harry
 */

#include <cmath>
#include "pch.h"
#include "Mouse.h"
#include "Polygon.h"

using namespace std;
using namespace Gdiplus;

/**
* Constructor
*/
CMouse::CMouse()
{
	mPolygon = make_shared<CPolygon>();
	mPolygon->CenteredSquare(76);
	mPolygon->SetImage(L"images/mouse.png");
}

/**
* Destructor
*/
CMouse::~CMouse()
{
}

/**
* Called every frame before draw
* \param elapsed Time in seconds since last update
*/
void CMouse::Update(double elapsed)
{
	double direction = copysign(1.0, GetPosition().X - mCheese->GetPosition().X);

	// Only moves the mouse if it is more than 70 pixels away from the cheese
	if (abs(mVirtualPositionX - mCheese->GetPosition().X) > 70)
	{
		SetPosition(Point(mStart.X + elapsed * mMoveSpeed * direction, GetPosition().Y));
		for (auto motor : mMotors)
		{
			motor->SetOn(false);
		}
	}
	else
	{
		for (auto motor : mMotors)
		{
			motor->SetOn(true);
		}
	}

	mVirtualPositionX = mStart.X + elapsed * mMoveSpeed * direction;
}

/**
* Setter for starting point
* \param start New starting point
*/
void CMouse::SetStart(Gdiplus::Point start)
{
	mStart = start;
}

/**
* Setter for move speed
* \param speed New move speed
*/
void CMouse::SetSpeed(double speed)
{
	mMoveSpeed = speed;
}

/**
* Setter for cheese
* \param cheese New cheese
*/
void CMouse::SetCheese(std::shared_ptr<CShape> cheese)
{
	mCheese = cheese;
}

/**
* Add a motor to the collection to be turned on
* when the mouse reaches to cheese
*/
void CMouse::AddMotor(std::shared_ptr<CMotor> motor)
{
	mMotors.push_back(motor);
}
