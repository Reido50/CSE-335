/**
 * \file AnimChannelAngle.h
 *
 * \author Reid Harry
 *
 * Animation channel for angles
 */

#pragma once
#include "AnimChannel.h"

/** Animation channel for angles */
class CAnimChannelAngle :
    public CAnimChannel
{
public:
    /** \brief Default constructor */
    CAnimChannelAngle();

    /** \brief Copy constructor disabled */
    CAnimChannelAngle(const CAnimChannelAngle&) = delete;
    /** \brief Assignment operator disabled */
    void operator=(const CAnimChannelAngle&) = delete;

    virtual ~CAnimChannelAngle();

    /** Getter for angle
    *   \returns Current angle */
    double GetAngle() { return mAngle; }

    void SetKeyframe(double angle);

    /** Removes a keyframe
    */
    void RemoveKeyframe();

    /** Keyframe class for handling angle */
    class KeyframeAngle : public Keyframe
    {
    public:
        /** Constructor
         * \param channel The channel we are for
         * \param angle The angle for the keyframe */
        KeyframeAngle(CAnimChannelAngle* channel, double angle) : Keyframe(channel), mChannel(channel), mAngle(angle) {}
        /** \brief Default constructor disabled */
        KeyframeAngle() = delete;
        /** \brief Copy constructor disabled */
        KeyframeAngle(const KeyframeAngle&) = delete;
        /** \brief Assignment operator disabled */
        void operator=(const KeyframeAngle&) = delete;
        /** Getter for angle 
        *   \returns Angle of the keyframe */
        double GetAngle() { return mAngle; }
        /** Setter for angle
        *   \param angle New angle */
        void SetAngle(double angle) { mAngle = angle; }
        /** Use this keyframe as keyframe 1 */
        virtual void UseAs1() override { mChannel->mKeyframe1 = this; }
        /** Use this keyframe as keyframe 2 */
        virtual void UseAs2() override { mChannel->mKeyframe2 = this; }
        /** Use this keyframe as the angle */
        virtual void UseOnly() override { mChannel->mAngle = mAngle; }
    private:
        /// Angle of the keyframe
        double mAngle;
        /// The channel this keyframe is associated with
        CAnimChannelAngle* mChannel;
    };

protected:
    void Tween(double t);

private:
    /// Current angle
    double mAngle = 0.0;

    /// The first angle keyframe
    KeyframeAngle* mKeyframe1 = nullptr;

    /// The second angle keyframe
    KeyframeAngle* mKeyframe2 = nullptr;
};

