/**
 * \file FishBeta.h
 *
 * \author Reid Harry
 *
 * Class that implements a Sparty fish
 */

#pragma once
#include<memory>

#include "Item.h"

 /**
  * Implements a Sparty fish
  */
class CFishSparty : public CItem
{
public:
	CFishSparty(CAquarium* aquarium);

	/// Default constructor (disabled)
	CFishSparty() = delete;

	/// Copy constructor (disabled)
	CFishSparty(const CFishSparty&) = delete;

	virtual void Draw(Gdiplus::Graphics* graphics) override;
	bool HitTest(int x, int y);

private:
	/// Bitmap image of the angler fish
	std::unique_ptr<Gdiplus::Bitmap> mFishImage;
};


