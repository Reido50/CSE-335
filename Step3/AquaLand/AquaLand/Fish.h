/**
 * \file Fish.h
 *
 * \author Reid Harry
 *
 * Base class for any fish in our aquarium
 */

#pragma once

#include "Item.h"
#include "XmlNode.h"
#include <memory>

/**
* Base class for a fish
* This applies to all of the fish, but no the decor
* items in the aquarium
*/
class CFish : public CItem
{
public:
	/// Default constructor (disabled)
	CFish() = delete;

	/// Copy constructor (disabled)
	CFish(const CFish&) = delete;

	/// The speed of the fish in the x direction
	/// \return The speed of the fish in the x direction
	double GetSpeedX() { return mSpeedX; }

	/// The speed of the fish in the y direction
	/// \return The speed of the fish in the y direction
	double GetSpeedY() { return mSpeedY; }

	/// Set the speed of the fish in the x direction
	/// \param speed Speed of the fish in the x direction
	void SetSpeedX(double speed) { mSpeedX = speed; }

	/// Set the speed of the fish in the y direction
	/// \param speed Speed of the fish in the y direction
	void SetSpeedY(double speed) { mSpeedY = speed; }

	void Update(double elapsed) override;

	std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node);

	void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node) override;

protected:
	CFish(CAquarium* aquarium, const std::wstring& filename);

private:
	/// Fish speed in the x direction
	double mSpeedX;

	/// Fish speed in the y direction
	double mSpeedY;
};

