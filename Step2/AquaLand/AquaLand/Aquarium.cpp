/**
 * \file Aquarium.cpp
 *
 * \author Reid Harry
 */

#include<memory>
#include<algorithm>
#include "pch.h"
#include "Aquarium.h"
#include "FishBeta.h"
#include "FishAngler.h"
#include<gdiplus.h>

using namespace Gdiplus;
using namespace std;

/**
 * Aquarium Constructor
 */
CAquarium::CAquarium()
{
	mBackground = unique_ptr<Gdiplus::Bitmap>(
		Bitmap::FromFile(L"images/background1.png"));
	if (mBackground->GetLastStatus() != Ok)
	{
		AfxMessageBox(L"Failed to open images/background.png");
	}

	
}

/**
 * Draw the aquarium
 * \param graphics The GDI+ graphics context to draw on
 */
void CAquarium::OnDraw(Gdiplus::Graphics* graphics)
{
	graphics->DrawImage(mBackground.get(), 0, 0,
		mBackground->GetWidth(), mBackground->GetHeight());

	FontFamily fontFamily(L"Arial");
	Gdiplus::Font font(&fontFamily, 16);

	SolidBrush green(Color(0, 64, 0));
	graphics->DrawString(L"Under the Sea!", -1,
						 &font, PointF(2, 2), &green);

	for (auto item : mItems)
	{
		item->Draw(graphics);
	}
}

/**
 * Add an item to the aquarium
 * \param item New item to add
 */
void CAquarium::Add(shared_ptr<CItem> item)
{
	mItems.push_back(item);
}

/**
 * Test an x, y click location to see if it clicked
 * on some item in the aquarium.
 * \param x X location
 * \param y Y location
 * \returns Pointer to item we clicked on or nullptr if none.
 */
shared_ptr<CItem> CAquarium::HitTest(int x, int y)
{
	for (auto i = mItems.rbegin(); i != mItems.rend(); i++)
	{
		if ((*i)->HitTest(x, y))
		{
			return *i;
		}
	}

	return nullptr;
}

/**
 * Moves the given item to the front of 
 * the scene to ensure it is moved first.
 * \param item Item to move to end of the vector
 */
void CAquarium::MoveToFront(std::shared_ptr<CItem> item)
{
	// Finds the item given and moves it to the end of the vector.
	auto loc = find(begin(mItems), end(mItems), item);
	if (loc != end(mItems))
	{
		mItems.erase(loc);
		mItems.push_back(item);
	}
}


/**
 * Checks to see if the given CFishAngler can catch anything
 * If it can, it will return the closest one to it.
 * \param x X location
 * \param y Y location
 * \returns Pointer to the closest item the CFishAngler can catch
 * or null ptr if it cannot catch anything
 */
shared_ptr<CItem> CAquarium::CatchTest(int x, int y)
{
	double minDist;
	shared_ptr<CItem> closest = nullptr;

	for (auto item : mItems)
	{
		if (item->GetX() != x || item->GetY() != y)
		{
			double dx = x - item->GetX();
			double dy = y - item->GetY();
			double dist = sqrt(dx * dx + dy * dy);

			if (dist <= 150.0)
			{
				if (closest == nullptr)
				{
					minDist = dist;
					closest = item;
				}
				else
				{
					if (dist < minDist)
					{
						minDist = dist;
						closest = item;
					}
				}
			}
		}
	}

	return closest;
}
