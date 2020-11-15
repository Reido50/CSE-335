/**
 * \file XmlLoader.cpp
 *
 * \author Jonathan Lee
 */

#include "pch.h"
#include "XmlLoader.h"
#include <memory>
#include "XmlNode.h"
#include <iostream>
#include "TileRoad.h"
#include "TileGrass.h"
#include "TileBuilding.h"
#include "TileTrees.h"
#include <string>

using namespace std;
using namespace Gdiplus;
using namespace xmlnode;

/**
 * Constructor of an XML Loader
 * \param towerGame TowerGame that the XmlLoader will load into
 */
CXmlLoader::CXmlLoader(CTowerGame* towerGame)
{
	mTowerGame = towerGame;
}

/**
 * Load the file from XML
 * \param filename The file to load
 * \return true if successful
 */
bool CXmlLoader::Load(std::wstring filename)
{
	try
	{
		std::shared_ptr<CXmlNode> root = xmlnode::CXmlNode::OpenDocument(filename.c_str());
		mWidth = root->GetAttributeValue(L"width", L"");
		mHeight = root->GetAttributeValue(L"height", L"");
		mStartX = root->GetAttributeValue(L"start-x", L"");
		mStartY = root->GetAttributeValue(L"start-y", L"");

		// Handling level logic
		mLevel = GetLevel(filename);
		mTowerGame->SetCurrentLevel(std::stoi(mLevel));

		for (auto child : root->GetChildren())
		{
			if (child->GetType() == NODE_ELEMENT)
			{
				wstring name = child->GetName();

				// Here we handle the different tags
				if (child->GetName() == L"declarations")
				{
					XmlDeclarations(child);
				}
				else if (child->GetName() == L"items")
				{
					XmlItems(child);
				}
			}
		}
	}
	catch (CXmlNode::Exception ex)
	{
		cout << ex.Message().c_str() << endl;
		return false;
	}
	return true;
}

/**
 * Handle the Xml node "declarations"
 * \param node The XML node
 */
void CXmlLoader::XmlDeclarations(std::shared_ptr<xmlnode::CXmlNode> node)
{
	for (auto child : node->GetChildren())
	{
		if (child->GetType() == NODE_ELEMENT)
		{
			std::wstring name = child->GetName();
			if (child->GetName() == L"road")
			{
				XmlDeclarationsRoad(child);
			}
			else if (child->GetName() == L"open")
			{
				XmlDeclarationsOpen(child);
			}
			else if (child->GetName() == L"house")
			{
				XmlDeclarationsHouse(child);
			}
			else if (child->GetName() == L"trees")
			{
				XmlDeclarationsTrees(child);
			}
		}
	}
}

/**
 * Handle the Xml node "road" that is within the "declaration" tag.
 * \param node The XML node
 */
void CXmlLoader::XmlDeclarationsRoad(std::shared_ptr<xmlnode::CXmlNode> node)
{
	auto declaredRoad = make_shared<CTileRoad>(node, mTowerGame);

	// Add to the collection
	mDeclared[declaredRoad->GetId()] = declaredRoad;
}

/**
 * Handle the Xml node "open" that is within the "declarations" tag.
 * \param node The XML node
 */
void CXmlLoader::XmlDeclarationsOpen(std::shared_ptr<xmlnode::CXmlNode> node)
{
	auto declaredOpen = make_shared<CTileGrass>(node, mTowerGame);

	// Add to the collection
	mDeclared[declaredOpen->GetId()] = declaredOpen;
}

/**
 * Handle the Xml node "house" that is within the "declarations" tag.
 * \param node The XML node
 */
void CXmlLoader::XmlDeclarationsHouse(std::shared_ptr<xmlnode::CXmlNode> node)
{
	auto declaredHouse = make_shared<CTileBuilding>(node, mTowerGame);

	// Add to the collection
	mDeclared[declaredHouse->GetId()] = declaredHouse;
}

/**
 * Handle the Xml node "trees" that is within the "declarations" tag.
 * \param node The XML node
 */
void CXmlLoader::XmlDeclarationsTrees(std::shared_ptr<xmlnode::CXmlNode> node)
{
	auto declaredTrees = make_shared<CTileTrees>(node, mTowerGame);

	// Add to the collection
	mDeclared[declaredTrees->GetId()] = declaredTrees;
}

/**
 * Handle the Xml node "items"
 * \param node The XML node
 */
void CXmlLoader::XmlItems(std::shared_ptr<xmlnode::CXmlNode> node)
{
	for (auto child : node->GetChildren())
	{
		if (child->GetType() == NODE_ELEMENT)
		{
			std::wstring name = child->GetName();
			if (child->GetName() == L"road")
			{
				XmlItemsRoad(child);
			}
			else if (child->GetName() == L"trees")
			{
				XmlItemsTrees(child);
			}
			else if (child->GetName() == L"open")
			{
				XmlItemsOpen(child);
			}
			else if (child->GetName() == L"house")
			{
				XmlItemsHouse(child);
			}
		}
	}
}

/**
 * Handle the "road" tag inside the "items" tag
 * \param node The XML node
 */
void CXmlLoader::XmlItemsRoad(std::shared_ptr<xmlnode::CXmlNode> node)
{
	// We get the id of the node
	auto id = node->GetAttributeValue(L"id", L"");

	// We get the member locations
	auto x = node->GetAttributeValue(L"x", L"");
	auto y = node->GetAttributeValue(L"y", L"");

	auto iterator = mDeclared.find(id);
	if (iterator != mDeclared.end())
	{
		auto define = iterator->second;

		std::wstring file = L"images/" + define->GetFile();
		auto road = make_shared<CTileRoad>(mTowerGame, file);
		road->SetType(GetRoadType(file));

		// If matches start tile load we swap image file
		if (x == mStartX && y == mStartY && road->GetType() == L"EW")
		{
			road->SetImage(L"roadEWstart.png");
			road->SetIsStart(true);
		}

		road->SetLocation(std::stoi(x) * 64, std::stoi(y) * 64);
		road->SetLevel(std::stoi(mLevel));

		mTowerGame->AddItem(road);
	}
}

/**
 * Handle the "open" tag inside the "items" tag
 * \param node The XML node
 */
void CXmlLoader::XmlItemsOpen(std::shared_ptr<xmlnode::CXmlNode> node)
{
	// We get the id of the node
	auto id = node->GetAttributeValue(L"id", L"");

	// We get the member locations
	auto x = node->GetAttributeValue(L"x", L"");
	auto y = node->GetAttributeValue(L"y", L"");

	auto iterator = mDeclared.find(id);
	if (iterator != mDeclared.end())
	{
		auto define = iterator->second;

		std::wstring file = L"images/" + define->GetFile();
		auto open = make_shared<CTileGrass>(mTowerGame, file);

		open->SetLocation(std::stoi(x) * 64, std::stoi(y) * 64);
		open->SetLevel(std::stoi(mLevel));
		mTowerGame->AddItem(open);
	}
}

/**
 * Handle the "house" tag inside the "items" tag
 * \param node The XML node
 */
void CXmlLoader::XmlItemsHouse(std::shared_ptr<xmlnode::CXmlNode> node) {
	// We get the id of the node
	auto id = node->GetAttributeValue(L"id", L"");

	// We get the member locations
	auto x = node->GetAttributeValue(L"x", L"");
	auto y = node->GetAttributeValue(L"y", L"");

	auto iterator = mDeclared.find(id);
	if (iterator != mDeclared.end())
	{
		auto define = iterator->second;

		std::wstring file = L"images/" + define->GetFile();
		auto house = make_shared<CTileBuilding>(mTowerGame, file);

		house->SetLocation(std::stoi(x) * 64, std::stoi(y) * 64);
		house->SetLevel(std::stoi(mLevel));
		mTowerGame->AddItem(house);
	}
}

/**
 * Handle the "trees" tag inside the "items" tag
 * \param node The XML node
 */
void CXmlLoader::XmlItemsTrees(std::shared_ptr<xmlnode::CXmlNode> node)
{
	// We get the id of the node
	auto id = node->GetAttributeValue(L"id", L"");

	// We get the member locations
	auto x = node->GetAttributeValue(L"x", L"");
	auto y = node->GetAttributeValue(L"y", L"");

	auto iterator = mDeclared.find(id);
	if (iterator != mDeclared.end())
	{
		auto define = iterator->second;

		std::wstring file = L"images/" + define->GetFile();
		auto trees = make_shared<CTileTrees>(mTowerGame, file);

		trees->SetLocation(std::stoi(x) * 64, std::stoi(y) * 64);
		trees->SetLevel(std::stoi(mLevel));
		mTowerGame->AddItem(trees);
	}
}

/**
 * Helper function to fetch road type from file name.
 * \param file XML File that the road type is being read from 
 * \returns Road type in string form
 */
std::wstring CXmlLoader::GetRoadType(std::wstring file)
{
	if (file.find(L"EW") != std::string::npos)
	{
		return L"EW";
	}
	else if (file.find(L"NE") != std::string::npos)
	{
		return L"NE";
	}
	else if (file.find(L"NS") != std::string::npos)
	{
		return L"NS";
	}
	else if (file.find(L"NW") != std::string::npos)
	{
		return L"NW";
	}
	else if (file.find(L"SE") != std::string::npos)
	{
		return L"SE";
	}
	else
	{
		return L"SW";
	}
}

/**
 * Helper function to fetch the level from file name
 * \param file that the Level is pulled from 
 * \return Level in string form
 */
std::wstring CXmlLoader::GetLevel(std::wstring file)
{
	if (file.find(L"0") != std::string::npos)
	{
		return L"0";
	}
	else if (file.find(L"1") != std::string::npos)
	{
		return L"1";
	}
	else if (file.find(L"2") != std::string::npos)
	{
		return L"2";
	}
	else
	{
		return L"3";
	}
}
