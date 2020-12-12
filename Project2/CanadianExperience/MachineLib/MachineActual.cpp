/**
 * \file MachineActual.cpp
 *
 * \author Reid Harry
 */

#include "pch.h"
#include "MachineActual.h"
#include "Assembly.h"
#include "Assembly1Factory.h"
#include "Assembly2Factory.h"

using namespace Gdiplus;

/** 
* Constructor
* /param machine Machine number to start with
*/
CMachineActual::CMachineActual(int machine)
{
	CMachineActual::SetMachineNumber(machine);
}

/** Destructor */
CMachineActual::~CMachineActual()
{

}

/**
* Used to draw the machine by drawing
* the assembly associated with it
* \param graphics Gdiplus drawing environment
*/
void CMachineActual::DrawMachine(Gdiplus::Graphics* graphics)
{
	mAssembly->Draw(graphics, mPosition);
}

/**
* Used to change frame number of the machine
* \param frame Frame number in the animation
*/
void CMachineActual::SetMachineFrame(int frame)
{
	if (frame < mFrame)
	{
		mFrame = 0;
		CMachineActual::SetMachineNumber(mNumber);
	}

	while (mFrame < frame) {
		mFrame++;
		mAssembly->Update(1.0 / mFrameRate);
	}
}

/**
* Used to change the assembly
* \param machine Machine number (1, 2, 3, ...)
*/
void CMachineActual::SetMachineNumber(int machine)
{
	mNumber = machine;

	if (machine == 1)
	{
		CAssembly1Factory factory;
		mAssembly = factory.CreateAssembly();
		mAssembly->SetMachine(this);
	}
	else if (machine == 2)
	{
		CAssembly2Factory factory;
		mAssembly = factory.CreateAssembly();
		mAssembly->SetMachine(this);
	}

	// Makes sure the mouse and pin get drawn in the correct place
	mAssembly->Update(0);
}

/**
* Getter for machine number
* \returns The current machine number
*/
int CMachineActual::GetMachineNumber()
{
	return mNumber;
}

/**
* Setter for the machine's position
* \param x X position
* \param y Y position
*/
void CMachineActual::SetLocation(int x, int y)
{
	mPosition = Point(x, y);
}
