/**
 * \file Cow.h
 *
 * \author Reid Harry
 *
 * Class that describes a Cow.
 * 
 * This class holds the characteristics of a cow.
 */

#pragma once

#include <string>

#include "Animal.h"

/**
* Class that describes a Cow.
* 
* Holds the characteristics of a cow.
*/
class CCow : public CAnimal
{
public:
	/// The types of cows we can have on our farm
	enum class Type {Bull, BeefCow, MilkCow};

	void ObtainCowInformation();

	void DisplayAnimal();

private:
	/// The cow's name
	std::string mName;

	/// The type of cow: Bull, BeefCow, or MilkCow
	Type mType = Type::MilkCow;

	/// The milk production for a cow in gallons per day
	double mMilkProduction = 0;
};

