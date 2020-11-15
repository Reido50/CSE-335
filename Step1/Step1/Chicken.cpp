/**
 * \file Chicken.cpp
 *
 * \author Reid Harry
 */

#include<iostream>
#include "leak.h"
#include "Chicken.h"

using namespace std;

/**
* Obtain a chicken description from the user.
*/
void CChicken::ObtainChickenInformation() 
{
	cout << endl;
	cout << "Input information about the chicken" << endl;

	// Obtain  the ID. This is easy since it's a 
	// string
	cout << "ID: ";
	cin >> mID;
}

/**
* Display the chicken.
*/
void CChicken::DisplayAnimal() 
{
	cout << "Chicken: " << mID << endl;
}