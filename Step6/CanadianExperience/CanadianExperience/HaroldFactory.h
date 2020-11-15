/**
 * \file HaroldFactory.h
 *
 * \author Reid Harry
 *
 * Factory class that builds the Harold character
 */

#pragma once

#include "Actor.h"
#include "ActorFactory.h"

/**
* Factory class that builds the Harold character
*/
class CHaroldFactory :
    public CActorFactory
{
public:
    std::shared_ptr<CActor> Create() override;
};

