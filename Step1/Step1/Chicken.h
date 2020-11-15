/**
 * \file Chicken.h
 *
 * \author Reid Harry
 *
 * Class that describes a chicken.
 */

#pragma once

#include<string>

#include "Animal.h"

/**
* Class that describes a chicken.
*/
class CChicken : public CAnimal
{
public:
	void ObtainChickenInformation();

	void DisplayAnimal();

	/**
	* Returns true if the chicken is hairy
	* 
	* Returns false always because all chickens are not hairy
	* 
	* \return true if the chicken is hairy
	*/
	bool IsHairy() { return false; };

private:
	/// The chicken's ID
	std::string mID;
};

