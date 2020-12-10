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

	if (abs(GetPosition().X - mCheese->GetPosition().X) > 70)
	{
		SetPosition(Point(mStart.X + elapsed * mMoveSpeed * direction, GetPosition().Y));
	}
	else
	{
		SetPosition(Point(mCheese->GetPosition().X + 70, mCheese->GetPosition().Y));
	}

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
