/**
 * \file Frisbee.cpp
 *
 * \author Sarah Swann
 */

#include "pch.h"
#include "Frisbee.h"
#include "ExplodingVisitor.h"
#include "Item.h"
#include "TowerGame.h"

/// Balloon filename 
const std::wstring FrisbeeImageName = L"images/frisbee.png";

/// Constant to convert radians to degrees
const double RtoD = 57.2957795;

/**
 * Constructor for CFrisbee
 * \param towerGame The CTowerGame the frisbee belongs to
 * \param speed Speed of the frisbee's movement
 * \param angle Angle of the frisbee's movement
 */
CFrisbee::CFrisbee(CTowerGame* towerGame, double speed, double angle) : CItem(towerGame, FrisbeeImageName)
{
	mSpeed = speed;
	mAngle = angle;
}

/**
 * Update function for CFrisbee
 * Called in OnPaint() once for every item in the TowerGame
 * \param elapsed Time in seconds since last OnPaint()
 */
void CFrisbee::Update(double elapsed)
{
	// Delete frisbee if it moves off the screen
	if (GetX() < 0 || GetY() < 0 || GetX() > CItem::GetTowerGame()->GetWidth() || GetY() > CItem::GetTowerGame()->GetHeight())
	{
		CItem::SetToDelete(true);
	}

	// Calculation for spinning
	mImageAngle += mAngularVelocity * elapsed;

	// Calculations for moving the frisbee in the direciton of mAngle
	double cs = cos(mAngle);
	double sn = -sin(mAngle);
	
	// The two ifs belong account for inaccuracy in double values
	if (abs(sn) < 0.0001)
	{
		sn = 0;
	}
	if (abs(cs) < 0.0001)
	{
		cs = 0;
	}

	SetLocation((double)GetX() + elapsed*cs*mSpeed, (double)GetY() + elapsed*sn*mSpeed);

	// Balloon collision detection
	CExplodingVisitor visitor;
	CItem::GetTowerGame()->Accept(&visitor);
	visitor.ExplodeBalloon(GetX(), GetY(), GetWidth(), "Frisbee");
}

/**
 * Draw function for CFrisbee
 * Called in OnPaint() once for every item in the TowerGame
 * \param graphics Gdiplis::Graphics the frisbee is drawn on
 */
void CFrisbee::Draw(Gdiplus::Graphics* graphics)
{
	double wid = GetImageWidth();
	double hit = GetImageHeight();

	// Must save and restore the graphics environment to enable rotation
	auto save = graphics->Save();
	graphics->TranslateTransform((Gdiplus::REAL)GetX(), (Gdiplus::REAL)GetY());
	graphics->RotateTransform((Gdiplus::REAL)(mImageAngle * RtoD));
	graphics->DrawImage(CItem::mImage.get(), (int)(-wid / 2), (int)(-hit / 2), (int)wid, (int)hit);
	graphics->Restore(save);
}