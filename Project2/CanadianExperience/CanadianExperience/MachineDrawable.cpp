/**
 * \file MachineDrawable.cpp
 *
 * \author Reid Harry
 */

#include "pch.h"
#include "MachineDrawable.h"
#include "MachineActual.h"
#include "MachineFactory.h"
#include "AnimChannelAngle.h"
#include "Timeline.h"

using namespace std;
using namespace Gdiplus;

/**
* Constructor
* \param name Name of the drawable
* \param machine Machine number to load in first
*/
CMachineDrawable::CMachineDrawable(const std::wstring& name, int machine) : CDrawable(name)
{
	CMachineFactory factory;
	mMachine = factory.CreateMachine();
	mMachine->SetMachineNumber(machine);
}

/**
* Destructor
*/
CMachineDrawable::~CMachineDrawable()
{
}

/**
* Used to draw the machine
* \param graphics Gdiplus drawing environment
*/
void CMachineDrawable::Draw(Gdiplus::Graphics* graphics)
{
	mMachine->SetLocation(GetPosition().X, GetPosition().Y);
	mMachine->SetMachineFrame(GetAngleChannel()->GetTimeline()->GetCurrentFrame());
	auto state = graphics->Save();
	graphics->ScaleTransform((float)mScale, (float)mScale);
	mMachine->DrawMachine(graphics);
	graphics->Restore(state);
}

/**
* Test if a given position on the screen hits the drawable
* \param pos Point on the screen to test
* \returns True if a hit
*/
bool CMachineDrawable::HitTest(Gdiplus::Point pos)
{
	return false;
}

/**
* Setter for the scale of the machine
* \param scale New scale
*/
void CMachineDrawable::SetScale(double scale)
{
	mScale = scale;
}
