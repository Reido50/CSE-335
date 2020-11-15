/**
 * \file Dart.cpp
 *
 * \author Reid Harry
 */

#include "pch.h"
#include "Dart.h"
#include "ExplodingVisitor.h"

/// Dart filename
const std::wstring DartImageName = L"images/dart.png";

CDart::~CDart()
{
}

CDart::CDart(CTowerGame* towerGame, CTowerEight* tower, double speed, double angle,
	double distanceFromTower) : CItem(towerGame, DartImageName) 
{
    mTower = tower;
	mSpeed = speed;
	mAngle = angle;
	mDistanceFromTower = distanceFromTower;
}

/**  Handle updates for animation
* \param elapsed The time since the last update
*/
void CDart::Update(double elapsed)
{
    mDistanceFromTower += elapsed * mSpeed;

	if (mDistanceFromTower >= 100)
	{
		SetToDelete(true);
	}

	// Calculations for moving the dart in the direciton of mAngle
	double cs = cos(mAngle);
	double sn = sin(mAngle);

	if (abs(sn) < 0.0001)
	{
		sn = 0;
	}

	if (abs(cs) < 0.0001)
	{
		cs = 0;
	}

	SetLocation(mTower->GetX() + (double)mTower->GetWidth()/2.0 + mDistanceFromTower*cs, mTower->GetY() + (double)mTower->GetHeight() / 2.0 + mDistanceFromTower * sn);

	CExplodingVisitor visitor;
	CItem::GetTowerGame()->Accept(&visitor);
	visitor.ExplodeBalloon(GetX(), GetY(), 10, "Eight");
}

/**
 * Draw the rotated dart. Rotation is determined by the member
 * variable mAngle, which is the rotation in radians.
 *
 * \param graphics The graphics context to draw on.
 * \ offsetX An X offset added to the position of the dart.
 * \ offsetY A Y offset added to the position of the dart.
 */
void CDart::Draw(Gdiplus::Graphics* graphics)
{
	int wid = (int)GetImageWidth();
	int hit = (int)GetImageHeight();

	auto save = graphics->Save();
	graphics->TranslateTransform((Gdiplus::REAL)GetX(), (Gdiplus::REAL)GetY());
	graphics->RotateTransform((Gdiplus::REAL)(mAngle * RtoD));
	graphics->DrawImage(CItem::mImage.get(), -wid / 2, -hit / 2, wid, hit);
	graphics->Restore(save);
}


