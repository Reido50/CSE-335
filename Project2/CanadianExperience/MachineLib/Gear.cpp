/**
 * \file Gear.cpp
 *
 * \author Reid Harry
 */

#include "pch.h"
#include "Gear.h"
#include "Polygon.h"

using namespace std;
using namespace Gdiplus;

/**
* Constructor
* \param radius Radius of the gear
* \param numTeeth Number of teeth the gear has
*/
CGear::CGear(double radius, int numTeeth)
{
	mRadius = radius;
	mNumTeeth = numTeeth;

	mPolygon = make_shared<CPolygon>();
	//mPolygon->CenteredSquare(50);
	mPolygon->Gear(mRadius, mNumTeeth);
}

/**
* Destructor
*/
CGear::~CGear()
{
}

/**
* Called every frame before draw
* \param elapsed Time in seconds since last update
*/
void CGear::Update(double elapsed)
{
}

/**
* Rotates the component by a certain amount of degrees
* \param rotation Amount to rotate by
*/
void CGear::Rotate(double rotation)
{
	mRotation += rotation;
	if (mSinks[0] != nullptr)
	{
		for (auto sink : mSinks)
		{
			if (sink->GetNumTeeth() == 0)
			{
				sink->Rotate(rotation);
			}
			else
			{
				sink->Rotate(-rotation * sink->GetNumTeeth() / mNumTeeth);
			}
		}
	}
}

/**
* Getter for number of teeth
* \returns Number of teeth the gear has
*/
int CGear::GetNumTeeth()
{
	return mNumTeeth;
}
