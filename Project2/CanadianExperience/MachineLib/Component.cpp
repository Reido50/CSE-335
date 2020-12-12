/**
 * \file Component.cpp
 *
 * \author Reid Harry
 */

#include "pch.h"
#include "Component.h"

CComponent::CComponent()
{
}

/**
* Rotates the component by a certain amount of degrees
* \param rotation Amount to rotate by
*/
void CComponent::SetRotation(double rotation)
{
	mRotation = rotation;
	if (mSinks.size() != 0)
	{
		for (auto sink : mSinks)
		{
			sink->SetRotation(rotation);
		}
	}
	
}

/**
* Draw the component
* \param graphics Gdiplus drawing enironment
* \param position Point to draw at
*/
void CComponent::Draw(Gdiplus::Graphics* graphics, Gdiplus::Point position)
{
	int drawX = position.X + mPosition.X;
	int drawY = position.Y + mPosition.Y;
	mPolygon->SetRotation(mRotation);
	mPolygon->DrawPolygon(graphics, drawX, drawY);
}

/**
* Setter for position
* \param position New position for the component
*/
void CComponent::SetPosition(Gdiplus::Point position)
{
	mPosition = position;
}

/**
* Setter for assembly
* \param assembly Assembly that houses the component
*/
void CComponent::SetAssembly(CAssembly* assembly)
{
	mAssembly = assembly;
}

/**
* Getter for position
* \returns Position of the component
*/
Gdiplus::Point CComponent::GetPosition()
{
	return mPosition;
}

/**
* Getter for Polygon
* \returns The polygon of the shape
*/
std::shared_ptr<CPolygon> CComponent::GetPolygon()
{
	return mPolygon;
}

/**
* Adds a sink to the sinks vector
* \param sink Sink to add
*/
void CComponent::AddSink(std::shared_ptr<CComponent> sink)
{
	mSinks.push_back(sink.get());
}

/**
* Setter for source
* \param source New source
*/
void CComponent::SetSource(std::shared_ptr<CComponent> source)
{
	mSource = source.get();
}

/**
* Used in determining if a component is using gear driven rotation
* \returns 0
*/
int CComponent::GetNumTeeth()
{
	return 0;
}

/**
* Used in determining if a component is using gear driven rotation
* \returns true
*/
bool CComponent::IsStacked()
{
	return true;
}

/**
* Getter for rotation
* \returns Rotation of the component
*/
double CComponent::GetRotation()
{
	return mRotation;
}
