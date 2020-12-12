/**
 * \file Pin.cpp
 *
 * \author Reid Harry
 */

#include "pch.h"
#include "Pin.h"

using namespace std;
using namespace Gdiplus;

/**
* Constructor
*/
CPin::CPin()
{
	mPolygon = make_shared<CPolygon>();
	mPolygon->CenteredSquare(300);
	mPolygon->SetImage(L"images/trap-pin.png");
}

/**
* Destructor
*/
CPin::~CPin()
{
}

/**
* Called every frame before draw
* \param elapsed Time since last update call
*/
void CPin::Update(double elapsed)
{
	SetPosition(Point(mCable->GetLength()-210, GetPosition().Y));
}

/**
* Setter for cable
* \param cable New cable
*/
void CPin::SetCable(CCable* cable)
{
	mCable = cable;
}

/**
* Setter for basket
* \param basket New basket
*/
void CPin::SetBasket(std::shared_ptr<CBasket> basket)
{
	mBasket = basket;
}
