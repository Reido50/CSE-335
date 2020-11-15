/**
 * \file Aquarium.h
 *
 * \author Reid Harry
 * 
 * Holds the CAquarium class
 */

#include"Item.h"
#include "FishAngler.h"

#include<memory>
#include<vector>

/**
 * Class that represents an Aquarium
 */
#pragma once
class CAquarium
{
public:
	CAquarium();

	void OnDraw(Gdiplus::Graphics * graphics);

	void Add(std::shared_ptr<CItem> item);

	std::shared_ptr<CItem> HitTest(int x, int y);

	void MoveToFront(std::shared_ptr<CItem> item);

	std::shared_ptr<CItem> CatchTest(int x, int y);

private:
	/// All of the items to populate our aqarium
	std::vector<std::shared_ptr<CItem> > mItems;

	std::unique_ptr<Gdiplus::Bitmap> mBackground;	///< Background image to use
};

