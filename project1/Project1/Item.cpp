/**
 * \file Item.cpp
 *
 * \author Reid Harry
 */

#include "pch.h"
#include "Item.h"
#include "XmlNode.h"
#include <string>

using namespace std;
using namespace Gdiplus;
using namespace xmlnode;

/// The directory containing the file images
const std::wstring CItem::ImagesDirectory = L"images/";

/// Used in hit test calculations
const int InsideTolerance = 64;

/// Constructor to load from node
/// \param node The node we are loading from
/// \param towerGame The tower game we are a part of
CItem::CItem(std::shared_ptr<xmlnode::CXmlNode> node, CTowerGame* towerGame)
{
    mId = node->GetAttributeValue(L"id", L"");
    mFile = node->GetAttributeValue(L"image", L"");

    mTowerGame = towerGame;
}

/**
 * Constructor
 * \param game CTowerGame object the item belogns to
 * \param filename Name of the image file for the item
 */
CItem::CItem(CTowerGame* game, const std::wstring& filename) : mTowerGame(game) 
{
    mImage = unique_ptr<Bitmap>(Bitmap::FromFile((L"../" + filename).c_str()));
    if (mImage->GetLastStatus() != Ok && filename != L"")
    {
        wstring msg(L"Failed to open ");
        msg += filename;
        AfxMessageBox(msg.c_str());
    }
}

/**
 * Destructor
 */
CItem::~CItem()
{
}

/** Accept a visitor
 * \param visitor The visitor we accept 
 */
void CItem::Accept(CItemVisitor* visitor)
{
}

/**
* brief Load the attributes for an item node.
*
* This is the  base class version that loads the attributes
* common to all items. Override this to load custom attributes
* for specific items.
*
* \param node The Xml node we are loading the item from
*/
void CItem::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    mX = node->GetAttributeIntValue(L"x", 0);
    mY = node->GetAttributeIntValue(L"y", 0);
}

/**
 * Draw function for CItem
 * Called in OnPaint() once for every item in the TowerGame
 * \param graphics Gdiplis::Graphics the item is drawn on
 */
void CItem::Draw(Gdiplus::Graphics* graphics)
{

    if (mImage != nullptr && mX != -1 && mY != -1)
    {
        int wid = mImage->GetWidth();
        int hit = mImage->GetHeight();

        graphics->DrawImage(mImage.get(),
            mX, mY, wid, hit);
    }
}

/**
 * Sets the image of the item
 * \param file Name of the image
 */
void CItem::SetImage(const std::wstring& file)
{
    if (!file.empty())
    {
        std::wstring filename = ImagesDirectory + file;
        mImage = std::unique_ptr<Bitmap>(Bitmap::FromFile((L"../" + filename).c_str()));
        if (mImage->GetLastStatus() != Ok)
        {
            std::wstring msg(L"Failed to open ");
            msg += filename;
            AfxMessageBox(msg.c_str());
            return;
        }
    }
    
    mFile = file;
}

/**
 * Test for a hit from given coordinates
 * \param x X value of the hit
 * \param y Y value of the hit
 * \return True
 */
bool CItem::HitTest(int x, int y)
{
    // Simple manhattan distance 
    return (abs(x - mX) + abs(y - mY)) <= InsideTolerance;
}