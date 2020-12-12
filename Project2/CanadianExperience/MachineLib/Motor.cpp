/**
 * \file Motor.cpp
 *
 * \author Reid Harry
 */

#include "pch.h"
#include "Motor.h"

using namespace std;
using namespace Gdiplus;

/**
* Constructor
*/
CMotor::CMotor()
{
	mPolygon = make_shared<CPolygon>();
	mPolygon->CenteredSquare(20);
	mPolygon->SetColor(Color::Gray);

	mBody = make_shared<CPolygon>();
	mBody->CenteredSquare(100);
	mBody->SetColor(Color::Black);
}

/**
* Destructor
*/
CMotor::~CMotor()
{
}

/**
* Called every frame before draw
* \param elapsed Time in seconds since last update
*/
void CMotor::Update(double elapsed)
{
	if (mOn && elapsed != 0.0)
	{
		SetRotation(GetRotation() + elapsed * mRotationSpeed);
	}
}

/**
* Draws the motor
* \param graphics Gdiplus drawing environment
* \param position Point to draw at
*/
void CMotor::Draw(Gdiplus::Graphics* graphics, Gdiplus::Point position)
{
	int drawX = position.X + GetPosition().X;
	int drawY = position.Y + GetPosition().Y;
	mBody->DrawPolygon(graphics, drawX, drawY);
	CComponent::Draw(graphics, position);
}

/**
* Setter for Rotation Speed
* \param rot New rotation speed
*/
void CMotor::SetRotationSpeed(double rot)
{
	mRotationSpeed = rot;
}

/**
* Setter for On
* \param on New on status
*/
void CMotor::SetOn(bool on)
{
	mOn = on;
}

/**
* Getter for the body of the motor
* \returns Body of the motor
*/
std::shared_ptr<CPolygon> CMotor::GetBody()
{
	return mBody;
}
