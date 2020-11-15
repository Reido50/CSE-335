/**
 * \file DecorCastle.cpp
 *
 * \author Reid Harry
 */

#include<string>
#include "pch.h"
#include "DecorCastle.h"
#include "XmlNode.h"

using namespace std;
using namespace xmlnode;

/// Castle decoration filename
const wstring DecorCastleImageName = L"images/castle.png";

/**
 * Constructor
 * \param aquarium Aquarium this decoration is a member of
 */
CDecorCastle::CDecorCastle(CAquarium* aquarium) :
	CItem(aquarium, DecorCastleImageName)
{
}

/**
* Save this item to an XML node
* \param node The node we are going to be a child of
*/
shared_ptr<CXmlNode> CDecorCastle::XmlSave(const shared_ptr<CXmlNode>& node)
{
	auto itemNode = CItem::XmlSave(node);

	itemNode->SetAttribute(L"type", L"castle");

	return itemNode;
}