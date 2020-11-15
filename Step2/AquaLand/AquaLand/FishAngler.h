/**
 * \file FishBeta.h
 *
 * \author Reid Harry
 *
 * Class that implements a Angler fish
 */

#pragma once
#include<memory>

#include "Item.h"

 /**
  * Implements a Angler fish
  */
class CFishAngler : public CItem
{
public:
	CFishAngler(CAquarium* aquarium);

	/// Default constructor (disabled)
	CFishAngler() = delete;

	/// Copy constructor (disabled)
	CFishAngler(const CFishAngler&) = delete;

	void SetLocation(double x, double y);

	virtual void Draw(Gdiplus::Graphics* graphics) override;
	bool HitTest(int x, int y);

private:
	/// Bitmap image of the angler fish
	std::unique_ptr<Gdiplus::Bitmap> mFishImage;

	/// Fish the angler has caught
	std::weak_ptr<CItem> mCaughtFish;
};




