/**
 * \file FishStinky.cpp
 *
 * \author Reid Harry
 */

#include "pch.h"
#include<string>
#include "FishStinky.h"
#include "XmlNode.h"

using namespace Gdiplus;
using namespace std;
using namespace xmlnode;

/// Maximum speed in the x direction in
/// pixels per second
const double MaxSpeedX = 20;

/// Maximum speed in the y direction in
/// pixels per second
const double MaxSpeedY = 20;

/// Minimum speed in the x direction in
/// pixels per second
const double MinSpeedX = 5;

/// Minimum speed in the y direction in
/// pixels per second
const double MinSpeedY = 5;

/// Fish filename
const wstring FishStinkyImageName = L"images/stinky.png";

/**
 * Constructor
 * \param aquarium Aquarium this fish is a member of
 */
CFishStinky::CFishStinky(CAquarium* aquarium) : 
	CFish(aquarium, FishStinkyImageName)
{
	CFish::SetSpeedX(MinSpeedX + ((double)rand() / RAND_MAX) * (MaxSpeedX-MinSpeedX));
	CFish::SetSpeedY(MinSpeedY + ((double)rand() / RAND_MAX) * (MaxSpeedY-MinSpeedY));
}

/**
* Save this item to an XML node
* \param node The node we are going to be a child of
*/
shared_ptr<CXmlNode> CFishStinky::XmlSave(const shared_ptr<CXmlNode>& node)
{
	auto itemNode = CFish::XmlSave(node);

	itemNode->SetAttribute(L"type", L"stinky");

	return itemNode;
}