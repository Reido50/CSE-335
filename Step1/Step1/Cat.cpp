/**
 * \file Cat.cpp
 *
 * \author Reid Harry
 */

#include<iostream>
#include "Cat.h"
#include "leak.h"

using namespace std;

/**
* Obtain information from the user about this cat.
*
* Asks the user for the information that describes a cat.
*/
void CCat::ObtainCatInformation() 
{
	cout << endl;
	cout << "Input information about the cat" << endl;

	// Obtain the name.
	// Must check if a name is valid (not empty and first char not a space)
	bool nameValid = false;
	while (!nameValid) 
	{
		cout << "Name: ";
		cin.ignore();
		getline(cin, mName);
		
		if (!mName.empty()) 
		{
			if (mName[0] != ' ')
			{
				nameValid = true;
			}
			else 
			{
				cout << "Invalid Name! Try again." << endl;
			}
		}
		else 
		{
			cout << "Invalid Name! Try again." << endl;
		}
	}

	// Obtain the breed using a loop.
	// We have a loop to handle errors
	bool breedValid = false;
	while (!breedValid)
	{
		cout << "1: American Shorthair" << endl;
		cout << "2: Persian" << endl;
		cout << "3. Siamese" << endl;
		cout << "4. Sphynx" << endl;
		cout << "Enter selection and return: ";
		int option;
		cin >> option;
		if (!cin)
		{
			// We have an error. Clear the input and try again
			cin.clear();
			cin.ignore();
			continue;
		}

		switch (option)
		{
		case 1:
			mBreed = Breed::AmericanShorthair;
			breedValid = true;
			break;

		case 2:
			mBreed = Breed::Persian;
			breedValid = true;
			break;

		case 3:
			mBreed = Breed::Siamese;
			breedValid = true;
			break;

		case 4:
			mBreed = Breed::Sphynx;
			breedValid = true;
			break;
		}
	}
}

/**
* Display the information about this cow
*/
void CCat::DisplayAnimal() 
{
	cout << mName << ": ";

	switch (mBreed) 
	{
	case Breed::AmericanShorthair:
		cout << "American Shorthair" << endl;
		break;

	case Breed::Persian:
		cout << "Persian" << endl;
		break;

	case Breed::Siamese:
		cout << "Siamese" << endl;
		break;

	case Breed::Sphynx:
		cout << "Sphynx" << endl;
		break;
	}
}

/**
* Returns true if the cat is hairy
* 
* All cats are hairy except the Sphynx
* 
* \return true if the cat is hair
*/
bool CCat::IsHairy() 
{
	if (mBreed == Breed::Sphynx) 
	{
		return false;
	}
	else
	{
		return true;
	}
}