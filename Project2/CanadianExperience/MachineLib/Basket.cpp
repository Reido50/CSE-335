/**
 * \file Basket.cpp
 *
 * \author Reid Harry
 */

#include "pch.h"
#include "Basket.h"

using namespace std;
using namespace Gdiplus;

/**
* Constructor
*/
CBasket::CBasket()
{
	mPolygon = make_shared<CPolygon>();
	mPolygon->CenteredSquare(300);
	mPolygon->SetImage(L"images/trap-trap.png");
}

/**
* Destructor
*/
CBasket::~CBasket()
{
}

/**
* Caled every frame before draw
* \param elapsed Time in seconds since last update
*/
void CBasket::Update(double elapsed)
{
	Gdiplus::Point pos = GetPosition();
	Gdiplus::Point pinPos = mPin->GetPosition();

	if (pinPos.X+10 < pos.X)
	{
		int newY;

		mVirtualPositionY += elapsed * mFallSpeed;

		if (mVirtualPositionY < mStart.Y)
		{
			newY = mStart.Y;
		}
		else if (mVirtualPositionY > mEnd.Y)
		{
			newY = mEnd.Y;
		}
		else
		{
			newY = mVirtualPositionY;
		}

		SetPosition(Point(mStart.X, newY));
	}
}

/**
* Setter for start
* \param start New start
*/
void CBasket::SetStart(Gdiplus::Point start)
{
	mStart = start;
	mEnd = Point(start.X, start.Y + 100);
}

/**
* Setter for speed
* \param speed New speed
*/
void CBasket::SetSpeed(double speed)
{
	mFallSpeed = speed;
}

/**
* Setter for pin
* \param pin New pin
*/
void CBasket::SetPin(std::shared_ptr<CPin> pin)
{
	mPin = pin;
}
