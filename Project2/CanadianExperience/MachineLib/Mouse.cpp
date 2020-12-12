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
	bool motorStatus = false;
	int newX;

	mVirtualPositionX -= elapsed * mMoveSpeed;

	if (mVirtualPositionX > mStart.X) 
	{
		newX = mStart.X;
	}
	else if (mVirtualPositionX < (double)mCheese->GetPosition().X + 70.0)
	{
		newX = mCheese->GetPosition().X + 70;
		motorStatus = true;
	}
	else
	{
		newX = mVirtualPositionX;
	}

	if (motorStatus)
	{
		for (auto motor : mMotors)
		{
			motor->SetOn(motorStatus);
		}
	}
	

	SetPosition(Point(newX, mStart.Y));
}

/**
* Setter for starting point
* \param start New starting point
*/
void CMouse::SetStart(Gdiplus::Point start)
{
	mStart = start;
	mVirtualPositionX = start.X;
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
* \param motor Motor to add
*/
void CMouse::AddMotor(std::shared_ptr<CMotor> motor)
{
	mMotors.push_back(motor);
}
