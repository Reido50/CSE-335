/**
 * \file Timeline.cpp
 *
 * \author Reid Harry
 */

#include "pch.h"
#include "Timeline.h"
#include "AnimChannel.h"

/**
* Constructor
*/
CTimeline::CTimeline()
{
}

/**
* Adds an animation channel to the timeline
* \param channel Animation channel to add
*/
void CTimeline::AddChannel(CAnimChannel* channel)
{
	mChannels.push_back(channel);
	channel->SetTimeline(this);
}

/**
* Removes a keyframe at the current frame
*/
void CTimeline::RemoveKeyframe()
{
	for (auto channel : mChannels)
	{
		channel->RemoveKeyframe(GetCurrentFrame());
	}
}

/**
* Sets the current time
* 
* Ensures all of the channels are
* valid for that point in time
* \param t T value
*/
void CTimeline::SetCurrentTime(double t)
{
	// Set the time
	mCurrentTime = t;

	for (auto channel : mChannels)
	{
		channel->SetFrame(GetCurrentFrame());
	}
}
