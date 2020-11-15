/**
 * \file DecorCastle.h
 *
 * \author Reid Harry
 *
 * Class that implements a castle decoration
 */

#pragma once
#include "Item.h"

/**
 * Implements a castle decoration
 */
class CDecorCastle : public CItem
{
public:
	CDecorCastle(CAquarium* aquarium);

	/// Default constructor (disabled)
	CDecorCastle() = delete;

	/// Copy constructor (disabled)
	CDecorCastle(const CDecorCastle&) = delete;

	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;
};