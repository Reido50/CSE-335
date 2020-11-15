/**
 * \file FishBeta.h
 *
 * \author Reid Harry
 *
 * Class that implements a Sparty fish
 */

#pragma once
#include "Fish.h"

 /**
  * Implements a Sparty fish
  */
class CFishSparty : public CFish
{
public:
	CFishSparty(CAquarium* aquarium);

	/// Default constructor (disabled)
	CFishSparty() = delete;

	/// Copy constructor (disabled)
	CFishSparty(const CFishSparty&) = delete;

	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;
};


