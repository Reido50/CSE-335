/**
 * \file TowerGame.cpp
 *
 *  Class that implements Tower Game
 */


#include "pch.h"
#include "TowerGame.h"
#include <algorithm>
#include "Item.h"
#include "Tower.h"
#include "TowerBomb.h"
#include "TowerCustom.h"
#include "TowerEight.h"
#include "TowerRing.h"
#include "XmlLoader.h"
#include "RoadVisitor.h"
#include "UpdateVisitor.h"
#include "TowerCopyVisitor.h"
#include "AnnouncerBegin.h"
#include "GoButton.h"
#include "MenuPalette.h"
#include "AnnouncerComplete.h"
#include "BalloonSpawner.h"
#include <iostream>

class CXmlLoader;

using namespace xmlnode;
using namespace Gdiplus;
using namespace std;

/// Game area in virtual pixels
const static int Width = 1224;

/// Game area height in virtual pixels
const static int Height = 1024;

/// Initial Towers X location
const int InitialX = 1124;

/// Initial TowerEight Y location
const int InitialY = 200;

/// Initial TowerRing Y location
const int InitialRingY = 100;

/// Initial TowerBomb Y location
const int InitialBombY = 300;

/// Initial TowerCustom Y location
const int InitialCustomY = 400;

/**
 * Constructor
 */
CTowerGame::CTowerGame()
{
}

/**
 * Destructor 
 */
CTowerGame::~CTowerGame()
{
}

/** Draw the gameboard
* \param graphics The GDI+ graphics context to draw with
* \param width the width of the window
* \param height the height of the window
*/
void CTowerGame::OnDraw(Gdiplus::Graphics* graphics, int width, int height)
{
    // Fill the background with black
    SolidBrush brush(Color::Black);
    graphics->FillRectangle(&brush, 0, 0, width, height);
    //
    // Automatic Scaling
    //
    float scaleX = float(width) / float(Width);
    float scaleY = float(height) / float(Height);
    mScale = min(scaleX, scaleY);

    // Ensure it is centered horizontally
    mXOffset = (float)((width - Width * mScale) / 2);

    // Ensure it is centered vertically
    mYOffset = (float)((height - Height * mScale) / 2);

    graphics->TranslateTransform(mXOffset, mYOffset);
    graphics->ScaleTransform(mScale, mScale);

    for (auto item : mItems)
    {
        item->Draw(graphics);
    }
}

/**
* Removes all flagged items from game
*/
void CTowerGame::RemoveToDelete()
{
    try {
        mItems.erase(
            std::remove_if(mItems.begin(), mItems.end(),
                [&](std::shared_ptr<CItem> item) { return item->GetToDelete(); }),
            mItems.end());
    }
    catch (exception& e) {
        std::cout << e.what() << std::endl;
    }
}

/**  Test an x,y click location to see if it clicked
* on some item in the game.
* \param x X location
* \param y Y location
* \return std::shared_ptr<CItem> Pointer to item we clicked on or nullptr if none.*/
std::shared_ptr<CItem> CTowerGame::HitTest(int x, int y)
{
    for (auto i = mItems.rbegin(); i != mItems.rend(); i++)
    {
        if ((*i)->HitTest(x, y))
        {
            return *i;
        }
    }

    return  nullptr;
}

/**
 * Test an x,y click location to see if it clicked an item
 * Safely casts from double to int
 * \param x X location
 * \param y Y location
 * \returns Pointer to item we clicked on or nullptr if none
 */
std::shared_ptr<CItem> CTowerGame::HitTest(double x, double y)
{
    return HitTest((int)x, (int)y);
}

/**  Move an item to the front of the list of items.
*
* Removes item from the list and adds it to the end so it
* will display last.
* \param item The item to move
*/
void CTowerGame::MoveToFront(std::shared_ptr<CItem> item)
{
    auto loc = find(::begin(mItems), ::end(mItems), item);
    if (loc != ::end(mItems))
    {
        mItems.erase(loc);
    }

    mItems.push_back(item);
}

/**
 * Makes a collection of all items hit by a given xy coordinate
 * \param x X coordinate
 * \param y Y coordinate
 * \returns Vector of pointers to items that were hit
 */
std::vector<std::shared_ptr<CItem>> CTowerGame::HitTestModified(int x, int y)
{
    std::vector<std::shared_ptr<CItem>> collection;
    for (auto i = mItems.rbegin(); i != mItems.rend(); i++)
    {
        if ((*i)->HitTest(x, y))
        {
            collection.push_back(*i);
        }
    }
    return collection;
}

/**
 * Makes a collection of all items hit by a given xy coordinate
 * \param x X coordinate
 * \param y Y coordinate
 * \returns Vector of pointers to items that were hit
 */
std::vector<std::shared_ptr<CItem>> CTowerGame::HitTestModified(double x, double y)
{
    return HitTestModified((int)x, (int)y);
}

/**
* Handle a click on the game area
* \param x X location clicked on
* \param y Y location clicked on
*/
void CTowerGame::ConvertToVirtualPixels(double &x, double &y)
{
    double oX = (x - mXOffset) / mScale;
    double oY = (y - mYOffset) / mScale;

    x = oX;
    y = oY;
}

/**  Add a item to the gameboard
* \param item New item to add
*/
void CTowerGame::AddItem(std::shared_ptr<CItem> item)
{
    mItems.push_back(item);
}

/**
 * Loads XML data
 * \param levelFile The level file we are loading
 * \return bool of when the level is loaded
 */
bool CTowerGame::Load(std::wstring levelFile)
{
    mIsActive = false;

    if (mCurrentLevel != -1)
    {
        mItems.clear();
    }
    // mCurrentLevel is reassigned in loader
    CXmlLoader loader = CXmlLoader(this);
    bool result = loader.Load(levelFile);

    if (!result)
    {
        mItems.clear();
        return result;
    }

    // Processing road pointers
    CRoadVisitor visitor;
    Accept(&visitor);
    visitor.ProcessRoads();

    mStartX = visitor.GetStart()->GetX() - 32;

    // Loading palette
    AddItem(std::make_shared<CMenuPalette>(this));

    // Loading beginning message
    AddItem(std::make_shared<CAnnouncerBegin>(this));

    return result;
}

/**
 * Sends visitor to all items on board
 * \param visitor Visitor going to the items
 */
void CTowerGame::Accept(CItemVisitor* visitor)
{ 
    for (auto item : mItems)
    {
        item->Accept(visitor);
    }   
}

/** Handle updates for animation
* \param elapsed The time since the last update
*/
void CTowerGame::Update(double elapsed)
{
    if (mIsActive && mBalloonCount <= 0)
    {
        std::cout << L"Woot" << std::endl;
    }
    // Level progression logic
    // If true, level has ended and we progress
    if (mIsActive && mBalloonCount <= 0 && mMessageState != MessageState::Spawning)
    {
        if (mMessageState == MessageState::None)
        {
            AddItem(std::make_shared<CAnnouncerComplete>(this));
        }
        else if (mMessageState == MessageState::Progress)
        {
            ProgressLevel();
        }
    }

    /// Changed to update visitor. Prevents updating tiles.
    CUpdateVisitor visitor = CUpdateVisitor(elapsed);
    for (auto item : mItems)
    {
        item->Accept(&visitor);
    }

    RemoveToDelete();
}

/**
 * Progresses level of game
 */
void CTowerGame::ProgressLevel()
{
    // We loop level 3 on complete
    if (mCurrentLevel == 3)
    {
        Load(L"../levels/level3.xml");
    }
    else
    {
        mCurrentLevel++;
        Load(L"../levels/level" + std::to_wstring(mCurrentLevel) + L".xml");
    }

    mMessageState = MessageState::None;
    mIsActive = false;
}

/**
 * Triggers startup lifecycle of level
 */
void CTowerGame::StartLevel()
{
    // If we are active we don't care.
    if (mIsActive)
    {
        return;
    }

    AddItem(make_shared<CBalloonSpawner>(this));
}

/**
 * Adds go button to screen.
 * Called once begin message is killed.
 */
void CTowerGame::AddGoButton()
{
    auto goButton = make_shared<CGoButton>(this);
    goButton->SetLocation(1100, 800);
    AddItem(goButton);
}

/**
 * Adds a balloon to the game and adds it to the start tile
 * \param balloon Shared pointer to the balloon to be added
 */
void CTowerGame::AddBalloon(shared_ptr<CBalloon> balloon)
{
    // Visitor to find and add balloon to start
    CRoadVisitor visitor;
    Accept(&visitor);
    visitor.GetStart()->AddBalloon(balloon);

    AddItem(balloon);

    /// We increment the balloon count for level logic
    mBalloonCount++;
}

/**
 * Creates an item specified by a type. Used in grabbing towers
 * \param type String of the type of tower eight, ring, bomb, or custom
 * \return std::shared_ptr<CItem> pointer to the item created*/
std::shared_ptr<CItem> CTowerGame::Validate(std::string type)
{
    // We don't want player grabbing anything
    // when message is up or game is active
    if (mMessageState == MessageState::Begin || mMessageState == MessageState::End || mIsActive)
    {
        return nullptr;
    }

    if (type == "eight")
    {
        auto TowerEight = make_shared<CTowerEight>(this);
        TowerEight->SetLocation(InitialX, InitialY);
        this->AddItem(TowerEight);
        return TowerEight;
    }
    if (type == "ring")
    {
        auto TowerRing = make_shared<CTowerRing>(this);
        TowerRing->SetLocation(InitialX, InitialRingY);
        this->AddItem(TowerRing);
        return TowerRing;
    }
    if (type == "bomb")
    {
        auto TowerBomb = make_shared<CTowerBomb>(this);
        TowerBomb->SetLocation(InitialX, InitialBombY);
        this->AddItem(TowerBomb);
        return TowerBomb;
    }
    if (type == "custom")
    {
        auto TowerCustom = make_shared<CTowerCustom>(this);
        TowerCustom->SetLocation(InitialX, InitialCustomY);
        this->AddItem(TowerCustom);
        return TowerCustom;
    }
    else
        return nullptr;
}

/**
 * Getter for the width of the game in virtual pixels
 * \return int width of the TowerGame
 */
int CTowerGame::GetWidth()
{
    return Width;
}

/**
 * Getter for height of the game in virtual pixels
 * \return int height of TowerGame
 */
int CTowerGame::GetHeight()
{
    return Height;
}