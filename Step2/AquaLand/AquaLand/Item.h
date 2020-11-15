/**
 * \file Item.h
 *
 * \author Reid Harry
 * 
 * Base class for any item in our aquarium
 */

#pragma once

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

	/// Set the item location
	/// \param x X location
	/// \param y Y location
	virtual void SetLocation(double x, double y) { mX = x; mY = y; }

	/// Set the item location when manipulated by the angler fish
	/// \param x X location
	/// \param y Y loctaion
	virtual void SetLocationAngler(double x, double y) { CItem::SetLocation(x, y); }

	/// Draw this item
	/// \param graphics Graphics device to draw on
	virtual void Draw(Gdiplus::Graphics* graphics) = 0;

	/**
	 * Test this item to see if it has been clicked on
	 * \param x X location of the aquarium to test
	 * \param y Y location of the aquarium to test
	 * \return true if clicked on
	 */
	virtual bool HitTest(int x, int y) = 0;

protected:
	CItem(CAquarium* aquarium);

private:
	/// This aquarium this item is contained in
	CAquarium* mAquarium;

	/// Item location in the aquarium
	double mX = 0;		///< X location for the center of the item
	double mY = 0;		///< Y location for the center of the item
};

