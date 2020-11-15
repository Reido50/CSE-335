/**
 * \file Aquarium.cpp
 *
 * \author Reid Harry
 */

#include "pch.h"
#include "Aquarium.h"
#include "FishBeta.h"
#include "FishStinky.h"
#include "FishSparty.h"
#include "DecorCastle.h"
#include<gdiplus.h>
#include<memory>
#include<algorithm>
#include "XmlNode.h"

using namespace Gdiplus;
using namespace std;
using namespace xmlnode;

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
 * Save the aquarium as a .aqua XML file.
 * 
 * Open an XML file and stream the aquarium data to it.
 * 
 * \param filename The filename of the file to save the aquarium to
 */
void CAquarium::Save(const std::wstring& filename)
{
	//
	// Create an XML document
	//
	auto root = CXmlNode::CreateDocument(L"aqua");

	// Iterate over all items and save them
	for (auto item : mItems)
	{
		item->XmlSave(root);
	}

	try
	{
		root->Save(filename);
	}
	catch (CXmlNode::Exception ex)
	{
		AfxMessageBox(ex.Message().c_str());
	}
}

/**
* Load the aquarium from a .aqua XML file.
* 
* Opens the XML file and reads the nodes, creating items as appropriate.
* 
* \param filename The filename of the file to load the aquarium from.
*/
void CAquarium::Load(const wstring& filename)
{
	// We surround with a try/catch to handle errors
	try
	{
		// Open the doucment to read
		shared_ptr<CXmlNode> root = CXmlNode::OpenDocument(filename);

		// Once we know it is open, clear the existing data
		Clear();

		//
		// Traverse the children of the root
		// node of the XML document in memory!!!!
		//
		for (auto node : root->GetChildren())
		{
			if (node->GetType() == NODE_ELEMENT && node->GetName() == L"item")
			{
				XmlItem(node);
			}
		}
	}
	catch (CXmlNode::Exception ex)
	{
		AfxMessageBox(ex.Message().c_str());
	}
}

/**
* Clear the aquarium data.
* 
* Deletes all known items in the aquarium
*/
void CAquarium::Clear()
{
	mItems.clear();
}

/**
* Handle an item node
* \param node Pointer to XML node we are handling
*/
void CAquarium::XmlItem(const shared_ptr<CXmlNode>& node)
{
	// A pointer for the tiem we are loading
	shared_ptr<CItem> item;

	// We have an item. What type?
	wstring type = node->GetAttributeValue(L"type", L"");
	if (type == L"beta")
	{
		item = make_shared<CFishBeta>(this);
	}
	else if (type == L"stinky")
	{
		item = make_shared<CFishStinky>(this);
	}
	else if (type == L"sparty")
	{
		item = make_shared<CFishSparty>(this);
	}
	else if (type == L"castle")
	{
		item = make_shared<CDecorCastle>(this);
	}

	if (item != nullptr)
	{
		item->XmlLoad(node);
		Add(item);
	}
}

/**
* Handle updates for animation
* \param elapsed The time since the last update
*/
void CAquarium::Update(double elapsed)
{
	for (auto item : mItems)
	{
		item->Update(elapsed);
	}
}