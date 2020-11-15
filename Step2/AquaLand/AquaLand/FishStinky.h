/**
 * \file FishBeta.h
 *
 * \author Reid Harry
 *
 * Class that implements a stinky fish
 */

#pragma once
#include<memory>

#include "Item.h"

 /**
  * Implements a stinky fish
  */
class CFishStinky : public CItem
{
public:
	CFishStinky(CAquarium* aquarium);

	/// Default constructor (disabled)
	CFishStinky() = delete;

	/// Copy constructor (disabled)
	CFishStinky(const CFishStinky&) = delete;

	virtual void Draw(Gdiplus::Graphics* graphics) override;
	bool HitTest(int x, int y);

private:
	/// Bitmap image of the angler fish
	std::unique_ptr<Gdiplus::Bitmap> mFishImage;
};

