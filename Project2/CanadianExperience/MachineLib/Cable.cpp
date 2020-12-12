/**
 * \file Cable.cpp
 *
 * \author Reid Harry
 */

#include "pch.h"
#include "Cable.h"
#include "Winch.h"

using namespace std;
using namespace Gdiplus;

/**
* Constructor
*/
CCable::CCable()
{
}

/**
* Destructor
*/
CCable::~CCable()
{
}

/**
* Draw the cable
* \param graphics
* \param position
*/
void CCable::Draw(Gdiplus::Graphics* graphics, Gdiplus::Point position)
{
	Pen pen(Color::Gray, 6);
	graphics->DrawLine(&pen, position.X, position.Y, position.X + mLength, position.Y);
}

/**
* Getter for the length
* \returns Length of the cable
*/
int CCable::GetLength()
{
	return mLength;
}

/**
* Getter for max length
* \returns Max length
*/
int CCable::GetMaxLength()
{
	return mMaxLength;
}

/**
* Setter for the winch
* \param winch New winch
*/
void CCable::SetWinch(CWinch* winch)
{
	mWinch = winch;
}

/**
* Increase/Decrease length
* \param length Additional length
*/
void CCable::Lengthen(double length)
{
	bool onStatus = true;

	mVirtualLength = length;
	if (mVirtualLength > mMaxLength)
	{
		mLength = mMaxLength;
	}
	else if (mVirtualLength < mMinLength)
	{
		mLength = mMinLength;
		onStatus = false;
	}
	else
	{
		mLength = mVirtualLength;
	}

	mWinch->SetOn(onStatus);
}

