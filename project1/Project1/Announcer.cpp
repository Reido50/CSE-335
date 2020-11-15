/**
 * \file Announcer.cpp
 *
 * \author Jonathan Lee
 */

#include "pch.h"
#include "Announcer.h"

using namespace Gdiplus;

/**
 * Base constructor to display messages
 */

 /**
  * Base constructor to display messages
  * \param towerGame game we are drawing our message on
  * \param message Message we are displaying
  * \param colorA color input for brush color
  * \param colorB color input for brush color
  * \param colorC color input for brush color
  */
CAnnouncer::CAnnouncer(CTowerGame* towerGame, std::wstring message, int colorA, int colorB, int colorC) : CItem(towerGame, L"")
{
	mMessage = message;
	mColorA = colorA;
	mColorB = colorB;
	mColorC = colorC;
	mFontSize = 16;
}

//Destructor
CAnnouncer::~CAnnouncer()
{
}

/**
 * Draw function override
 * \param graphics Graphics system we draw to
 */
void CAnnouncer::Draw(Gdiplus::Graphics* graphics)
{
	// If message is empty we don't care
	if (mMessage == L"") 
	{
		return;
	}

	FontFamily fontFamily(L"Arial");
	Gdiplus::Font font(&fontFamily,(Gdiplus::REAL)mFontSize);

	SolidBrush color(Color(mColorA, mColorB, mColorC));
	graphics->DrawString(mMessage.c_str(), -1, &font, PointF((Gdiplus::REAL)GetX(), (Gdiplus::REAL)GetY()), &color);
}

/** Accept a visitor
* \param visitor The visitor we accept */
void CAnnouncer::Accept(CItemVisitor* visitor)
{
}
