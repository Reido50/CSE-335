/**
 * \file AnimChannelPosition.cpp
 *
 * \author Reid Harry
 */

#include "pch.h"
#include <memory>
#include "AnimChannelPosition.h"

using namespace std;
using namespace Gdiplus;

CAnimChannelPosition::CAnimChannelPosition()
{
}

CAnimChannelPosition::~CAnimChannelPosition()
{
}

/**
* Set a keyframe
*
* This function allocates a new keyframe and sends it to
* CAnimChannel, which will insert it into the collection of keyframes.
* \param position Position for the keyframe.
*/
void CAnimChannelPosition::SetKeyframe(Point position)
{
	// Create a keyframe of the appropriate type
	// telling it this channel and the position
	shared_ptr<KeyframePosition> keyframe = make_shared<KeyframePosition>(this, position);

	// Insert it into the collection
	InsertKeyframe(keyframe);
}

void CAnimChannelPosition::Tween(double t)
{
	Point a = mKeyframe1->GetPosition();
	Point b = mKeyframe2->GetPosition();

	mPosition = Point(int(a.X + t * (b.X - a.X)), int(a.Y + t * (b.Y - a.Y)));
}
