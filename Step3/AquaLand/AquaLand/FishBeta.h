/**
 * \file FishBeta.h
 *
 * \author Reid Harry
 *
 * Class that implements a Beta fish
 */

#pragma once
#include "Fish.h"
#include "XmlNode.h"
#include <memory>

/**
 * Implements a Beta fish
 */
class CFishBeta : public CFish
{
public:
	CFishBeta(CAquarium* aquarium);

	/// Default constructor (disabled)
	CFishBeta() = delete;

	/// Copy constructor (disabled)
	CFishBeta(const CFishBeta&) = delete;

	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;
};

