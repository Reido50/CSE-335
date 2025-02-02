/**
 * \file AnimChannelAngle.cpp
 *
 * \author Reid Harry
 */

#include "pch.h"
#include <memory>
#include "AnimChannelAngle.h"
#include "Timeline.h"

using namespace std;

CAnimChannelAngle::CAnimChannelAngle()
{
}

CAnimChannelAngle::~CAnimChannelAngle()
{
}

/**
* Set a keyframe
* 
* This function allocates a new keyframe and sends it to
* CAnimChannel, which will insert it into the collection of keyframes.
* \param angle Angle for the keyframe.
*/
void CAnimChannelAngle::SetKeyframe(double angle)
{
	// Create a keyframe of the appropriate type
	// telling it this channel and the angle
	shared_ptr<KeyframeAngle> keyframe = make_shared<KeyframeAngle>(this, angle);

	// Insert it into the collection
	InsertKeyframe(keyframe);
}

/**
* Compute an angle that is an interpolation between two keyframes
* 
* This function is called after Use1 and Use2, so we have pointers to
* the valid keyframes of the type KeyframeAngle. This function does the
* tweening.
* \param t A t value. t=0 means keyframe1, t=1 means keyframe2. Other values
* interpolate between.
*/
void CAnimChannelAngle::Tween(double t)
{
	mAngle = mKeyframe1->GetAngle() * (1 - t) + mKeyframe2->GetAngle() * t;
}
