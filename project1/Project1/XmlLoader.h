/**
 * \file XmlLoader.h
 *
 * \author Jonathan Lee
 *
 * Base class to load nested load
 */

#pragma once
#include <string>
#include <memory>
#include "XmlNode.h"
#include <map>

class CTowerGame;
class CItem;

/** XML Loader class that loads levels */
class CXmlLoader
{
public:
	CXmlLoader(CTowerGame* towerGame);

	CXmlLoader() = delete;

	bool Load(std::wstring filename);

private:
	/// The declaration loading method
	void XmlDeclarations(std::shared_ptr<xmlnode::CXmlNode> node);
	/// The declaration loading method
	void XmlDeclarationsRoad(std::shared_ptr<xmlnode::CXmlNode> node);
	/// The declaration loading method
	void XmlDeclarationsOpen(std::shared_ptr<xmlnode::CXmlNode> node);
	/// The declaration loading method
	void XmlDeclarationsHouse(std::shared_ptr<xmlnode::CXmlNode> node);
	/// The declaration loading method
	void XmlDeclarationsTrees(std::shared_ptr<xmlnode::CXmlNode> node);
	/// The item loading method
	void XmlItems(std::shared_ptr<xmlnode::CXmlNode> node);
	/// The item loading method
	void XmlItemsRoad(std::shared_ptr<xmlnode::CXmlNode> node);
	/// The item loading method
	void XmlItemsOpen(std::shared_ptr<xmlnode::CXmlNode> node);
	/// The item loading method
	void XmlItemsTrees(std::shared_ptr<xmlnode::CXmlNode> node);
	/// The item loading method
	void XmlItemsHouse(std::shared_ptr<xmlnode::CXmlNode> node);
	/// Road helper method
	std::wstring GetRoadType(std::wstring file);
	/// Level helper method
	std::wstring GetLevel(std::wstring file);

	/// width of the item
	std::wstring mWidth;
	/// height of the item
	std::wstring mHeight;
	/// starting road tile location X
	std::wstring mStartX;
	/// starting road tile location Y
	std::wstring mStartY;
	/// level that is being loaded in
	std::wstring mLevel;

	/// Map of declarations loaded from XML
	std::map<std::wstring, std::shared_ptr<CItem>> mDeclared;

	/// TowerGame this is loading into
	CTowerGame* mTowerGame;
};

