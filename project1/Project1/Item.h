/**
 * \file Item.h
 *
 * \author Reid Harry
 *
 * Base class for all items
 */

#pragma once
#include <memory>
#include <string>
#include "XmlNode.h"
#include "ItemVisitor.h"

class CTowerGame;

 /** Base class for all items */
class CItem
{
public:
	/// How much we offset drawing the tile to the left of the center
	const static int OffsetLeft = 64;

	/// How much we offset drawing the tile above the center
	const static int OffsetDown = 32;

	/// Constructor
	CItem(std::shared_ptr<xmlnode::CXmlNode> node, CTowerGame* towerGame);

	/// Destructor
	virtual ~CItem();

	/// Default constructor
	CItem() = delete;

	/// Copy constructor
	CItem(const CItem&) = delete;

	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CItemVisitor* visitor);

	virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);

	static const std::wstring ImagesDirectory;

	virtual bool HitTest(int x, int y);

	/// Set the item location
	/// \param x X location
	/// \param y Y location
	void SetLocation(int x, int y) { mX = x; mY = y; }

	/// Set the item location
	/// \param x X location string
	/// \param y Y location string
	void SetLocation(std::wstring x, std::wstring y) { mX = std::stoi(x); mY = std::stoi(y); }

	/// Set the item location
	/// \param x X location
	/// \param y Y location
	void SetLocation(double x, double y) { mX = (int)x; mY = (int)y; }

	/// The x location of the center of the tile
	/// \return X location in pixels
	int GetX() const { return mX; }

	/// The y location of the center of the tile
	/// \return Y location in pixels
	int GetY() const { return mY; }

	/// Getter for the width of the item's mImage
	/// \returns int Width of the item's mImage
	int GetWidth() const { return mImage->GetWidth(); }

	/// Getter for the height of the item's mImage
	/// \returns int Height of the item's mImage
	int GetHeight() const { return mImage->GetHeight(); }

	void SetImage(const std::wstring& file);

	/// Get the file name for this item image
	/// \returns Filename or blank if none
	std::wstring GetFile() { return mFile;  }

	/// Get the id for this item loaded from Xml
	/// \returns Id
	std::wstring GetId() { return mId; }

	virtual void Draw(Gdiplus::Graphics* graphics);

	/// Handle updates for animation
	/// \param elapsed The time since the last update
	virtual void Update(double elapsed) {}

	/// Get the towergame this item is in
	/// \returns TowerGame pointer
	CTowerGame* GetTowerGame() { return mTowerGame; }

	/// Get the height of item image
	/// \returns double Height of image
	double GetImageHeight() { return mImage->GetHeight(); }

	/// Get the width of item image
	/// \returns double Width of image
	double GetImageWidth() { return mImage->GetWidth(); }

	/// Sets level member
	/// \param level Level this tile is a part of
	void SetLevel(int level) { mLevel = level; }

	/// Fetches level tile is a part of
	/// \returns Level
	int GetLevel() { return mLevel; }

	/// Sets member delete variable
	/// \param toDelete Bool value
	virtual void SetToDelete(bool toDelete) { mToDelete = toDelete; }

	/// Gets toDelete variable
	/// \return bool ToDelete
	virtual bool GetToDelete() { return mToDelete; }

protected:
	CItem(CTowerGame* game, const std::wstring& filename);

	/// The item's bitmap image
	std::unique_ptr<Gdiplus::Bitmap> mImage;

private:
	/// The game this item is contained in
	CTowerGame* mTowerGame;

	/// X location of the item
	int mX = -1;

	/// Y location of the item
	int mY = -1;

	/// File location of the image
	/// Loaded from declaration in XML
	std::wstring mFile;

	/// The ID for this definition
	std::wstring mId;

	/// The level this item is loaded for
	/// If -1 it is defaulted and shouldn't be unloaded
	/// This applies to buttons, displays, etc.
	int mLevel = -1;

	/// True if the item should be deleted
	bool mToDelete = false;
};