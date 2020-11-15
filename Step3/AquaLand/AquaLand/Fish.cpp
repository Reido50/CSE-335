/**
 * \file Fish.cpp
 *
 * \author Reid Harry
 */

#include "pch.h"
#include<string>
#include "Fish.h"
#include "Aquarium.h"
#include "XmlNode.h"

using namespace std;
using namespace xmlnode;

/**
* Constructor
* \param aquarium The aquarium we are in
* \param filename Filename for the image we use
*/
CFish::CFish(CAquarium* aquarium, const wstring& filename) :
	CItem(aquarium, filename)
{
}

/**
* Handle updates in time of our fish
* 
* This is called before we draw and allows us to 
* move our fish. We add our speed times the amount
* of time that has elapsed
*/
void CFish::Update(double elapsed)
{
	SetLocation(GetX() + mSpeedX * elapsed, 
		GetY() + mSpeedY * elapsed);

	// Handles fish swimming to the left and right border
	if (mSpeedX > 0 && GetX() >= GetAquarium()->GetWidth() - 10 - CItem::GetItemWidth()/2)
	{
		mSpeedX = -mSpeedX;
		SetMirror(mSpeedX < 0);
	}
	else if (mSpeedX < 0 && GetX() <= 0 + 10 + CItem::GetItemWidth()/2)
	{
		mSpeedX = -mSpeedX;
		SetMirror(mSpeedX < 0);
	}

	// Handles fish swimming to the top and bottom border
	if (mSpeedY > 0 && GetY() >= GetAquarium()->GetHeight() - 10 - CItem::GetItemHeight() / 2)
	{
		mSpeedY = -mSpeedY;
	}
	else if (mSpeedY < 0 && GetY() <= 0 + 10 + CItem::GetItemHeight() / 2)
	{
		mSpeedY = -mSpeedY;
	}
}

/**
* Save this fish to an XML node
* \param node The node we are going to be a child of
*/
shared_ptr<CXmlNode> CFish::XmlSave(const shared_ptr<CXmlNode>& node)
{
	auto itemNode = node->AddChild(L"item");

	itemNode->SetAttribute(L"x", GetX());
	itemNode->SetAttribute(L"y", GetY());
	itemNode->SetAttribute(L"speedx", mSpeedX);
	itemNode->SetAttribute(L"speedy", mSpeedY);

	return itemNode;
}

/**
* Load the attributes for a fish node.
*
* \param node The Xml node we are loading the fish from
*/
void CFish::XmlLoad(const shared_ptr<CXmlNode>& node)
{
	CItem::XmlLoad(node);
	mSpeedX = node->GetAttributeDoubleValue(L"speedx", 0);
	mSpeedY = node->GetAttributeDoubleValue(L"speedy", 0);
	SetMirror(mSpeedX < 0);
}

