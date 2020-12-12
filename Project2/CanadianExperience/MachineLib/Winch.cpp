/**
 * \file Winch.cpp
 *
 * \author Reid Harry
 */

#include "pch.h"
#include "Winch.h"

using namespace std;
using namespace Gdiplus;

/**
* Constructor
*/
CWinch::CWinch()
{
	mPolygon = make_shared<CPolygon>();
	mPolygon->CenteredSquare(64);
	mPolygon->SetImage(L"images/drum.png");

	mCable.SetWinch(this);
}

/**
* Destructor
*/
CWinch::~CWinch()
{
}

/**
* Called once per frame before draw
* \param elapsed Time in seconds since last update
*/
void CWinch::Update(double elapsed)
{
}

/**
* Draws the winch
* \param graphics Gdiplus drawing environment
* \param position Point to draw at
*/
void CWinch::Draw(Gdiplus::Graphics* graphics, Gdiplus::Point position)
{
	CComponent::Draw(graphics, position);

	Point cablePos = Point(GetPosition().X + position.X, GetPosition().Y + position.Y - 32);
	mCable.Draw(graphics, cablePos);
}

/**
* Rotates the winch
* \param rotation Amount to rotate by
*/
void CWinch::SetRotation(double rotation)
{

	mCable.Lengthen(mCable.GetLength() + mSpeed * (rotation - GetRotation()));
	if (mOn)
	{
		CComponent::SetRotation(rotation);
	}	
	
}

/**
* Setter for on
* \param on New on status
*/
void CWinch::SetOn(bool on)
{
	mOn = on;
}

/**
* Getter for cable
* \returns Cable the winch pulls
*/
CCable* CWinch::GetCable()
{
	return &mCable;
}
