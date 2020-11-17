/**
 * \file Actor.h
 *
 * \author Reid Harry
 *
 * Class for actors in our drawings
 */

#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Drawable.h"
#include "AnimChannelPosition.h"

class CPicture;

/**
* Class for actors in our drawings
* 
* An actors is some graphical object that consists of
* one or more parts. Actors can be animated
*/
class CActor
{
public:
    CActor(const std::wstring& name);

    /** Default constructor disabled */
    CActor() = delete;
    /** Copy constructor disabled */
    CActor(const CActor&) = delete;
    /** Assignment operator disabled */
    void operator=(const CActor&) = delete;

    virtual ~CActor();

    void SetRoot(std::shared_ptr<CDrawable> root);
    void Draw(Gdiplus::Graphics* graphics);
    std::shared_ptr<CDrawable> HitTest(Gdiplus::Point pos);
    void AddDrawable(std::shared_ptr<CDrawable> drawable);
    
    virtual void SetTimeline(CTimeline* timeline);

    virtual void SetKeyframe();

    virtual void GetKeyframe();

    /** Get the actor name
     * \returns Actor name */
    std::wstring GetName() const { return mName; }

    /** The actor position
    * \returns The actor position as a point */
    Gdiplus::Point GetPosition() const { return mPosition; }

    /** The actor position
    * \param pos The new actor position */
    void SetPosition(Gdiplus::Point pos) { mPosition = pos; }

    /** Actor is enabled
    * \returns enabled status */
    bool IsEnabled() const { return mEnabled; }

    /** Set Actor Enabled
    * \param enabled New enabled status */
    void SetEnabled(bool enabled) { mEnabled = enabled; }

    /** Actor is clickable
    * \returns true if actor is clickable */
    bool IsClickable() const { return mClickable; }

    /** Actor clickable
    * \param clickable New clickable status */
    void SetClickable(bool clickable) { mClickable = clickable; }

    /** Get the actor picture
    * \returns Picture the actor is in */
    CPicture* GetPicture() { return mPicture; }

    void SetPicture(CPicture* picture);

    /** The position animation channel
     * \returns Pointer to position channel */
    CAnimChannelPosition* GetPositionChannel() { return &mChannel; }

private:
    /// Name of the actor
    std::wstring mName;

    /// Enabled status of the actor
    bool mEnabled = true;

    /// Position of the actor
    Gdiplus::Point mPosition = Gdiplus::Point(0, 0);

    /// Clickable status of the actor
    bool mClickable = true;

    /// The root drawable
    std::shared_ptr<CDrawable> mRoot;

    /// The drawables in drawing order
    std::vector<std::shared_ptr<CDrawable>> mDrawablesInOrder;

    /// The picture the actor is in
    CPicture* mPicture = nullptr;

    /// The animation channel for animating movement of the actor
    CAnimChannelPosition mChannel;
};

