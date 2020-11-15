/**
 * \file FishBeta.h
 *
 * \author Reid Harry
 *
 * Class that implements a Beta fish
 */

#pragma once
#include<memory>

#include "Item.h"

/**
 * Implements a Beta fish
 */
class CFishBeta : public CItem
{
public:
	CFishBeta(CAquarium* aquarium);

	/// Default constructor (disabled)
	CFishBeta() = delete;

	/// Copy constructor (disabled)
	CFishBeta(const CFishBeta&) = delete;

	virtual void Draw(Gdiplus::Graphics* graphics) override;
	bool HitTest(int x, int y);

private:
	/// Bitmap image of the angler fish
	std::unique_ptr<Gdiplus::Bitmap> mFishImage;
};

