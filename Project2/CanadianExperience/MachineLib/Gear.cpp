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
void CGear::SetRotation(double rotation)
{
	if (mMaxRotation == -1.0 || rotation < mMaxRotation)
	{
		mRotation = rotation;
		if (mSinks.size() != 0)
		{
			for (auto sink : mSinks)
			{
				if (sink->GetNumTeeth() == 0 || sink->IsStacked())
				{
					sink->SetRotation(rotation);
				}
				else
				{
					// For some reason it looks more like the example program when I flip the fraction of teeth
					//sink->SetRotation(-rotation * (((double)sink->GetNumTeeth()) / ((double)mNumTeeth)));
					sink->SetRotation(-rotation * (((double)mNumTeeth) / ((double)sink->GetNumTeeth())));
				}
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

/**
* Getter for the stacked flag
* \returns The current stacked status
*/
bool CGear::IsStacked()
{
	return mStacked;
}

/**
* Setter for stacked
* \param stacked New stacked status
*/
void CGear::SetStacked(bool stacked)
{
	mStacked = stacked;
}

/**
* Setter for max rotation
* \param maxRot New max rotation
*/
void CGear::SetMaxRotation(double maxRot)
{
	mMaxRotation = maxRot;
}
