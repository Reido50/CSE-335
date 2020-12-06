/**
 * \file Component.cpp
 *
 * \author Reid Harry
 */

#include "pch.h"
#include "Component.h"

/**
* Rotates the component by a certain amount of degrees
* \param rotation Amount to rotate by
*/
void CComponent::Rotate(double rotation)
{
	mRotation += rotation;
}

/**
* Draw the component
* \param graphics Gdiplus drawing enironment
* \param position Point to draw at
*/
void CComponent::Draw(Gdiplus::Graphics* graphics, Gdiplus::Point position)
{
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
