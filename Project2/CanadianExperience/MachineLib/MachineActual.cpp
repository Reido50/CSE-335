/**
 * \file MachineActual.cpp
 *
 * \author Reid Harry
 */

#include "pch.h"
#include "MachineActual.h"
#include "Assembly.h"

using namespace Gdiplus;

/** 
* Constructor
* /param machine Machine number to start with
*/
CMachineActual::CMachineActual(int machine)
{
	mNumber = machine;
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
}

/**
* Used to change the assembly
* \param machine Machine number (1, 2, 3, ...)
*/
void CMachineActual::SetMachineNumber(int machine)
{
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
