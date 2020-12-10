/**
 * \file Mouse.cpp
 *
 * \author Reid Harry
 */

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
	mPolygon->Rectangle(0, 0, 76, 76);
	mPolygon->SetColor(Color::White);
	mPolygon->SetImage(L"/images/mouse.png");
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
