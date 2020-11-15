/**
 * \file Farm.h
 *
 * \author Reid Harry
 *
 * Class that describes a Farm.
 * 
 * This class holds a collection of animals that make
 * up inventory of a farm.
 */

#pragma once

#include <vector>
#include "Cow.h"
#include "Animal.h"

/**
* Class that describes a farm.
* 
* Holds a collection of animals that make up the farm
* inventory.
*/
class CFarm
{
public:
	void AddAnimal(CAnimal* animal);
	void DisplayInventory();
	int HairyAnimalCount();
	~CFarm();

private:
	/// A list with the inventory of all animals on the farm
	std::vector<CAnimal*> mInventory;
};

