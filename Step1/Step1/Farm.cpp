/**
 * \file Farm.cpp
 *
 * \author Reid Harry
 */

#include "leak.h"
#include "Farm.h"

 /**
 * Add an animal to the farm inventory.
 *
 * \param animal An animal to add to the inventory
 */
void CFarm::AddAnimal(CAnimal* animal)
{
	mInventory.push_back(animal);
}

/**
* Display the farm inventory.
*/
void CFarm::DisplayInventory() 
{
	for (auto animal : mInventory) 
	{
		animal->DisplayAnimal();
	}
}

/**
* CFarm destructor
*/
CFarm::~CFarm() 
{
	// Iterate over all of the animals, destroying
	// each one
	for (auto animal : mInventory) 
	{
		delete animal;
	}

	// And clear the list
	mInventory.clear();
}


/**
* Returns the amount of hairy animals in the farm
* 
* \return Integer value of how many hairy animals are in the farm
*/
int CFarm::HairyAnimalCount() 
{
	int count = 0;
	for (auto animal : mInventory)
	{
		// Adds 1 to count if the animal is hairy and adds a 0 otherwise
		count += animal->IsHairy();
	}
	return count;
}