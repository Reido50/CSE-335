/**
 * \file SpartyFactory.h
 *
 * \author Reid Harry
 *
 * Factory class that builds the Sparty character
 */

#pragma once

#include "Actor.h"
#include "ActorFactory.h"

/**
* Factory class that builds the Sparty character
*/
class CSpartyFactory :
    public CActorFactory
{
public:
    std::shared_ptr<CActor> Create() override;
};

