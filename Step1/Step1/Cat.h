/**
 * \file Cat.h
 *
 * \author Reid Harry
 *
 * Class that describes a cat.
 */

#pragma once

#include "Animal.h"

#include<string>

/**
* Class that describes a cat.
*/
class CCat : public CAnimal
{
public:
	/// The breeds of cats we can have on our farm
	enum class Breed {AmericanShorthair, Persian, Siamese, Sphynx};

	void ObtainCatInformation();

	void DisplayAnimal();

	bool IsHairy();

private:
	/// The name of the cat.
	std::string mName;

	/// The breed of the cat: AmericanShorthair, Persian, Siamese, or Sphynx
	Breed mBreed = Breed::AmericanShorthair;
};

