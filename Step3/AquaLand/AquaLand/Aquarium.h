/**
 * \file Aquarium.h
 *
 * \author Reid Harry
 * 
 * Holds the CAquarium class
 */

#include"Item.h"

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

	/// Get the width of the aquarium
	/// \returns Aquarium width
	int GetWidth() const { return mBackground->GetWidth(); }

	/// Get the height of the aquarium
	/// \returns Aquarium height
	int GetHeight() const { return mBackground->GetHeight(); }

	void OnDraw(Gdiplus::Graphics * graphics);

	void Add(std::shared_ptr<CItem> item);

	std::shared_ptr<CItem> HitTest(int x, int y);

	void MoveToFront(std::shared_ptr<CItem> item);

	std::shared_ptr<CItem> CatchTest(int x, int y);

	void Save(const std::wstring& filename);

	void Load(const std::wstring& filename);

	void Clear();

	void Update(double elapsed);

private:
	/// All of the items to populate our aqarium
	std::vector<std::shared_ptr<CItem> > mItems;

	std::unique_ptr<Gdiplus::Bitmap> mBackground;	///< Background image to use

	void XmlItem(const std::shared_ptr<xmlnode::CXmlNode>& node);
};

