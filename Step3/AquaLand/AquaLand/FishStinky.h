/**
 * \file FishBeta.h
 *
 * \author Reid Harry
 *
 * Class that implements a stinky fish
 */

#pragma once
#include "Fish.h"

 /**
  * Implements a stinky fish
  */
class CFishStinky : public CFish
{
public:
	CFishStinky(CAquarium* aquarium);

	/// Default constructor (disabled)
	CFishStinky() = delete;

	/// Copy constructor (disabled)
	CFishStinky(const CFishStinky&) = delete;

	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;
};

