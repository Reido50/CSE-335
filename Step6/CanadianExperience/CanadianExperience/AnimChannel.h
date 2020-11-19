/**
 * \file AnimChannel.h
 *
 * \author Reid Harry
 *
 * Base class for animation channels
 */

#pragma once

#include <string>
#include <memory>
#include <vector>

class CTimeline;

/**
* Base class for animation channels
* 
* This class provides basic functionality and a polymorphic
* representation for animation channels.
*/
class CAnimChannel
{
public:
    /** \brief Default constructor */
    CAnimChannel();

    /** \brief Copy constructor disabled */
    CAnimChannel(const CAnimChannel&) = delete;
    /** \brief Assignment operator disabled */
    void operator=(const CAnimChannel&) = delete;

    virtual ~CAnimChannel();

    bool IsValid();

    void SetFrame(int currFrame);

    /** Getter for name
    *   \returns Name of the channel */
    std::wstring GetName() { return mName; }

    /** Setter for name
    *   \param name New name of the channel */
    void SetName(std::wstring name) { mName = name; }

    /** Getter for the timeline
    *   \returns Timeline of the channel */
    CTimeline* GetTimeline() { return mTimeline; }

    /** Setter for timeline
    *   \param timeline New timeline of the channel */
    void SetTimeline(CTimeline* timeline) { mTimeline = timeline; }

    void RemoveKeyframe(int frame);

    /** Class that represents a keyframe */
    class Keyframe
    {
    public:
        /** Constructor
         * \param channel Channel we are associated with */
        Keyframe(CAnimChannel* channel) : mChannel(channel) {}
        /** \brief Default constructor disabled */
        Keyframe() = delete;
        /** \brief Copy constructor disabled */
        Keyframe(const Keyframe&) = delete;
        /** \brief Assignment operator disabled */
        void operator=(const Keyframe&) = delete;
        /** Getter for frame 
        *   \returns the frame number */
        int GetFrame() { return mFrame; }
        /** Setter for frame
        *   \param frame New frame number */
        void SetFrame(int frame) { mFrame = frame; }
        virtual void UseAs1() = 0;  ///< Abstract function Use as 1
        virtual void UseAs2() = 0;  ///< Abstract function Use as 2
        virtual void UseOnly() = 0; ///< Abstract function Use only
    protected:
        /// Frame number
        int mFrame;
    private:
        /// The channel this keyframe is associated with
        CAnimChannel* mChannel;
    };

protected:
    virtual void InsertKeyframe(std::shared_ptr<Keyframe> keyframe);

    virtual void Tween(double t);

private:
    /// Name of the animation channel
    std::wstring mName;

    /// The first keyframe
    int mKeyframe1 = -1;
    /// The second keyframe
    int mKeyframe2 = -1;

    /// The collection of keyframes for this channel
    std::vector<std::shared_ptr<Keyframe>> mKeyframes;

    /// The timeline object
    CTimeline* mTimeline = nullptr;
};

