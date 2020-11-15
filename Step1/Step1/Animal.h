/**
 * \file Animal.h
 *
 * \author Reid Harry
 *
 * Class that describes an animal
 */

#pragma once
/**
* Class that describes an animal
*/
class CAnimal
{
public:
	virtual ~CAnimal();

	/** Displays an animal. */
	virtual void DisplayAnimal() {};

	/** 
	* Returns true if the animal is hairy
	* 
	* Assumes all animals are hairy
	* 
	* \return true if the animal is hairy
	*/
	virtual bool IsHairy() { return true; };
};

