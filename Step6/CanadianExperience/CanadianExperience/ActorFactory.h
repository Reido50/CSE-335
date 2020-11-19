/**
 * \file ActorFactory.h
 *
 * \author Reid Harry
 *
 * Abstract base class for actor factories
 */

#pragma once

#include <memory>

class CActor;

/**
* Abstract base class for actor factories
*/
class CActorFactory
{
public:
	/** Create function is abstract 
	*   \returns Created actor */
	virtual std::shared_ptr<CActor> Create() = 0;
};

