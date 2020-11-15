/**
 * \file Item.h
 *
 * \author Reid Harry
 * 
 * Base class for any item in our aquarium
 */

#pragma once
#include<memory>
#include<string>
#include "XmlNode.h"

class CAquarium;

/**
 * Base class for any item in our aquarium.
 */
class CItem
{
public:
	/// Default constructor (disabled)
	CItem() = delete;

	/// Copy constructor
	CItem(const CItem&) = delete;

	virtual ~CItem();

	/** The X location of the item
	 * \return X location in pixels */
	double GetX() { return mX; }

	/** The y location of the item
	 * \return Y location in pixels */
	double GetY() { return mY; }

	/** The aquarium the item is in
	 *  \return CAquarium the item is in*/
	CAquarium* GetAquarium() { return mAquarium; }

	/// The width of the item
	/// \return The width of the item image
	double GetItemWidth() { return mItemImage->GetWidth(); }

	/// The height of the item
	/// \return The height of the item image
	double GetItemHeight() { return mItemImage->GetHeight(); }

	/// Set the item location
	/// \param x X location
	/// \param y Y location
	virtual void SetLocation(double x, double y) { mX = x; mY = y; }

	/// Set the mirror status
	/// \param m New mirror flag
	void SetMirror(bool m) { mMirror = m; }

	/// Draw this item
	/// \param graphics Graphics device to draw on
	virtual void Draw(Gdiplus::Graphics* graphics);

	/**
	 * Test this item to see if it has been clicked on
	 * \param x X location of the aquarium to test
	 * \param y Y location of the aquarium to test
	 * \return true if clicked on
	 */
	virtual bool HitTest(int x, int y);

	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node);

	virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);

	/// Handle updates for animation
	/// \param elapsed The time since the last update
	virtual void Update(double elapsed) {};

protected:
	CItem(CAquarium* aquarium, const std::wstring &filename);

private:
	/// This aquarium this item is contained in
	CAquarium* mAquarium;

	/// Item location in the aquarium
	double mX = 0;		///< X location for the center of the item
	double mY = 0;		///< Y location for the center of the item

	/// The image of this fish
	std::unique_ptr<Gdiplus::Bitmap> mItemImage;

	bool mMirror = false;	///< True mirrors the item image
};

