/**
 * \file TowerGame.h
 *
 *  Class that implements Tower Game
 */

#pragma once
#include <memory>
#include <vector>
#include <map>
#include <utility>
#include "XmlNode.h"
#include "Item.h"
#include "ItemVisitor.h"

/**
* Implements tower game with the items and tiles
*/
class CTowerGame
{
public: 
	CTowerGame();

	/// Destructor
	virtual ~CTowerGame();

    /// Enum type of messages displayed on screen
    enum class MessageState { None, Begin, End, Progress, Spawning };

	/// The spacing between grid locations
	static const int GridSpacing = 32;

	void OnDraw(Gdiplus::Graphics* graphics, int width, int height);
    
    void RemoveToDelete();
  
    void ConvertToVirtualPixels(double& x, double& y);
    
    void AddItem(std::shared_ptr<CItem> item);
   
    void AddBalloon(std::shared_ptr<CBalloon> balloon);

    bool Load(std::wstring levelFile);
    
    /**
    * Get the number of items in the game
    * \returns the number of items
    */
    size_t GetSize() { return mItems.size(); }

    std::shared_ptr<CItem> CTowerGame::HitTest(int x, int y);

    std::shared_ptr<CItem> HitTest(double x, double y);

    void MoveToFront(std::shared_ptr<CItem> item);

    std::vector<std::shared_ptr<CItem>> HitTestModified(int x, int y);

    std::vector<std::shared_ptr<CItem>> HitTestModified(double x, double y);

	void Update(double elapsed);

    void Accept(CItemVisitor* visitor);

    /// Sets current level
    /// \param level Level to be set
    void SetCurrentLevel(int level) { mCurrentLevel = level; }

    /// Gets current level of game
    /// \return int Level
    int GetCurrentLevel() { return mCurrentLevel; }

    /// Used to increase player score
    /// \param amount Amount to increase by
    void IncreaseScore(int amount) { mScore += amount; }

    /// Used to decrease player score
    /// \param amount Amount to decrease by
    void DecreaseScore(int amount) { mScore -= amount; }

    /// Getter for the width of the game in virtual pixels
    /// \return int width of TowerGame
    int GetWidth();

    /// Getter for height of the game in virtual pixels
    /// \return int height of TowerGame
    int GetHeight();

    /// Fetches player score
    /// \returns Score
    int GetScore() { return mScore; }

    /// Automatically lowers balloon count on board
    void DecreaseBalloonCount() { mBalloonCount -= 1; }

    /// Gets current amount of balloons
    /// \return int number of balloons
    int GetBalloonCount() { return mBalloonCount; }

    /// Gets starting x coord of map
    /// \return int coord
    int GetStartX() { return mStartX; }

    /// Message state of screen
    /// \param state MessageState we are setting
    void SetMessageState(MessageState state) { mMessageState = state; }

    /// Determines if level is currently active
    /// \return bool True if level is active
    bool IsActive() { return mIsActive; }

    /// Change level to Active 
    /// set True, level is active
    void SetActive() { mIsActive = true; }

    /// Adds go button to screen
    void AddGoButton();

    /// Triggers startup lifecycle of level
    void StartLevel();

    std::shared_ptr<CItem> Validate(std::string type);

    /** Iterator Class */
    class Iter
    {
    public:
        /** Constructor
         * \param game The TowerGame we are iterating over
         * \param pos The position
         */
        Iter(CTowerGame* game, int pos) : mGame(game), mPos(pos) {}

        /** Test for end of the iterator
        * \param other any other iterator
         * \returns True if we this position equals not equal to the other position */
        bool operator!=(const Iter& other) const
        {
            return mPos != other.mPos;
        }

        /** Get value at current position
         * \returns Value at mPos in the collection */
        std::shared_ptr<CItem> operator *() const { return mGame->mItems[mPos]; }

        /** Increment the iterator
         * \returns Reference to this iterator */
        const Iter& operator++()
        {
            mPos++;
            return *this;
        }

    private:
        CTowerGame* mGame;   ///< TowerGame we are iterating over
        int mPos;       ///< Position in the collection
    };

    /** Get an iterator for the beginning of the collection
     * \returns Iter object at position 0 */
    Iter begin() { return Iter(this, 0); }

    /** Get an iterator for the end of the collection
     * \returns Iter object at position past the end */
    Iter end() { return Iter(this, mItems.size()); }

private:
	/// all items in the tower game
	std::vector<std::shared_ptr<CItem> > mItems; //all items

	/// Virtual Pixels scale
	float mScale = 0;
	/// virtual pixels offset X
	float mXOffset = 0;
    /// virtual pixels offset Y
	float mYOffset = 0;

    /// Current level being loaded into game
    int mCurrentLevel = -1;
    /// Current score of the game
    int mScore = 0;
    /// If true, level is currently running
    bool mIsActive = false;
    /// Tracking number of balloons on level
    int mBalloonCount = 0;
    /// If true, Locks screen from grabbing
    MessageState mMessageState = MessageState::None;

    /// Used to start the game
    int mStartX = -1;

    /// Responsible for progressing level loading
    void ProgressLevel();
};

