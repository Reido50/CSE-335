/**
 * \file Assembly.cpp
 *
 * \author Reid Harry
 */

#include "pch.h"
#include "Assembly.h"

/**
* Default Constructor
*/
CAssembly::CAssembly()
{

}

/**
* Destructor
*/
CAssembly::~CAssembly()
{

}

/**
* Used for drawing the assembly and
* all the components it contains
* \param graphics Gdiplus Graphics environment
* \param position Gdiplus point for where to draw
*/
void CAssembly::Draw(Gdiplus::Graphics* graphics, Gdiplus::Point position)
{
}

/**
* Used to update all the components
* of the assembly
* \param elapsed Amount of seconds passed
*/
void CAssembly::Update(double elapsed)
{
}

/**
* 
*/
void CAssembly::AddComponent(std::shared_ptr<CComponent> component)
{
	mComponents.push_back(component);
	component->SetAssembly(this);
}
