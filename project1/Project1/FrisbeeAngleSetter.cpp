/**
 * \file FrisbeeAngleSetter.cpp
 *
 * \author Reid Harry
 */

#include "pch.h"
#include "FrisbeeAngleSetter.h"
#include "TowerCustom.h"

/**
 * Constructor
 * \param point Pointer to the point the CTowerCustom will shoot at
 */
CFrisbeeAngleSetter::CFrisbeeAngleSetter(CPoint* point)
{
	mPoint = point;
}

/**
 * Visitor function for CTowerCustom
 * Calculates and sets the angle based on mPoint
 * \param tower Pointer to a CTowerCustom
 */
void CFrisbeeAngleSetter::VisitTowerCustom(CTowerCustom* tower)
{
	CPoint origin((int)(tower->GetX()+tower->GetWidth()/2), (int)(tower->GetY()+tower->GetHeight()/2));

	// Implementation of angle between vectors formula
	// cos(theta) = (dot product of v1 and v2)/((magnitude of v1)*(magnitude of v2))
	CPoint v1(1, 0);
	CPoint v2(mPoint->x - origin.x, mPoint->y - origin.y);

	// Added casting to prevent arithmetic overflow
	double dot = (double)v1.x * (double)v2.x + (double)v1.y * (double)v2.y;
	double magv1 = sqrt((double)v1.x * (double)v1.x + (double)v1.y * (double)v1.y);
	double magv2 = sqrt((double)v2.x * (double)v2.x + (double)v2.y * (double)v2.y);
	double result = acos(dot / (magv1 * magv2));

	// Fixed bug with frisbees shooting backwards
	if (mPoint->y > origin.y)
	{
		result = -result;
	}

	tower->SetAngle(result);
}