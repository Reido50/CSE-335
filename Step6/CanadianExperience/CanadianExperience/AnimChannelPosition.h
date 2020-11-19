/**
 * \file AnimChannelPosition.h
 *
 * \author Reid Harry
 *
 * Animation channel for position
 */

#pragma once
#include "AnimChannel.h"

/**
* Animation channel for position
*/
class CAnimChannelPosition :
    public CAnimChannel
{
public:
    /** \brief Default constructor */
    CAnimChannelPosition();

    /** \brief Copy constructor disabled */
    CAnimChannelPosition(const CAnimChannelPosition&) = delete;
    /** \brief Assignment operator disabled */
    void operator=(const CAnimChannelPosition&) = delete;

    virtual ~CAnimChannelPosition();

    /** Getter for position 
    *   \returns Current position */
    Gdiplus::Point GetPosition() { return mPosition; }

    void SetKeyframe(Gdiplus::Point position);

    /** Keyframe class for handling position */
    class KeyframePosition : public Keyframe
    {
    public:
        /** Constructor
        * \param channel The channel we are for
        * \param position The position for the keyframe */
        KeyframePosition(CAnimChannelPosition* channel, Gdiplus::Point position) : Keyframe(channel), mChannel(channel), mPosition(position) {}
        /** \brief Default constructor disabled */
        KeyframePosition() = delete;
        /** \brief Copy constructor disabled */
        KeyframePosition(const KeyframePosition&) = delete;
        /** \brief Assignment operator disabled */
        void operator=(const KeyframePosition&) = delete;
        /** Getter for position 
        *   \returns Position of the keyframe */
        Gdiplus::Point GetPosition() { return mPosition; }
        /** Setter for position
        *   \param position New position */
        void SetPosition(Gdiplus::Point position) { mPosition = position; }
        /** Use this keyframe as keyframe 1 */
        virtual void UseAs1() override { mChannel->mKeyframe1 = this; }
        /** Use this keyframe as keyframe 2 */
        virtual void UseAs2() override { mChannel->mKeyframe2 = this; }
        /** Use this keyframe as the angle */
        virtual void UseOnly() override { mChannel->mPosition = mPosition; }
    private:
        /// Position of the keyframe
        Gdiplus::Point mPosition;
        /// The channel this keyframe is associated with
        CAnimChannelPosition* mChannel;
    };

protected:
    void Tween(double t);

private:
    /// Current position
    Gdiplus::Point mPosition = Gdiplus::Point(0, 0);

    /// The first position keyframe
    KeyframePosition* mKeyframe1 = nullptr;

    /// The second position keyframe
    KeyframePosition* mKeyframe2 = nullptr;
};

