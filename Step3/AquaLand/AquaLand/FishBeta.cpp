/**
 * \file FishBeta.cpp
 *
 * \author Reid Harry
 */

#include "pch.h"
#include<string>
#include "FishBeta.h"

using namespace Gdiplus;
using namespace std;
using namespace xmlnode;

/// Maximum speed in the x direction in
/// pixels per second
const double MaxSpeedX = 100;

/// Maximum speed in the y direction in
/// pixels per second
const double MaxSpeedY = 60;

/// Minimum speed in the x direction in
/// pixels per second
const double MinSpeedX = 75;

/// Minimum speed in the y direction in
/// pixels per second
const double MinSpeedY = 40;

/// Fish filename
const wstring FishBetaImageName = L"images/beta.png";

/**
 * Constructor
 * \param aquarium Aquarium this fish is a member of
 */
CFishBeta::CFishBeta(CAquarium* aquarium) : 
	CFish(aquarium, FishBetaImageName)
{
	CFish::SetSpeedX(MinSpeedX + ((double)rand() / RAND_MAX) * (MaxSpeedX - MinSpeedX));
	CFish::SetSpeedY(MinSpeedY + ((double)rand() / RAND_MAX) * (MaxSpeedY - MinSpeedY));
}

/**
* Save this item to an XML node
* \param node The node we are going to be a child of
*/
shared_ptr<CXmlNode> CFishBeta::XmlSave(const shared_ptr<CXmlNode> &node)
{
	auto itemNode = CFish::XmlSave(node);

	itemNode->SetAttribute(L"type", L"beta");

	return itemNode;
}