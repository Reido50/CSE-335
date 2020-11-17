/**
 * \file HeadTop.cpp
 *
 * \author Reid Harry
 */

#include "pch.h"
#include "HeadTop.h"
#include "Actor.h"
#include "Timeline.h"

using namespace std;
using namespace Gdiplus;

/// Constant ratio to convert radians to degrees
const double RtoD = 57.295779513;

/**
* Constructor
* \param name Name of the HeadTop drawable
* \param filename Name of the image file of the HeadTop drawable
*/
CHeadTop::CHeadTop(const std::wstring& name, const std::wstring& filename) : CImageDrawable(name, filename)
{
}

/**
* Draws the HeadTop
* \param graphics Graphics object we are drawing to
*/
void CHeadTop::Draw(Gdiplus::Graphics* graphics)
{
    // Draw the HeadTop image
	CImageDrawable::Draw(graphics);

    if (mLeftEye.IsLoaded() && mRightEye.IsLoaded())
    {
        // Determine the point on the screen were we will draw the left eye
        Point leye = TransformPoint(Point(42, 79));
        // And draw the bitmap there
        mLeftEye.DrawImage(graphics, leye, mPlacedR);

        // Repeat the process for the right eye.
        Point reye = TransformPoint(Point(69, 79));
        mRightEye.DrawImage(graphics, reye, mPlacedR);
    }
    else
    {
        // Draw the eyebrows
        DrawEyebrow(graphics, TransformPoint(mLeftEyebrowPosition), TransformPoint(mLeftEyebrowPosition + Point(12, -2)));
        DrawEyebrow(graphics, TransformPoint(mRightEyebrowPosition), TransformPoint(mRightEyebrowPosition + Point(13, 2)));

        //Draw the eyes
        DrawEye(graphics, TransformPoint(mLeftEyePosition));
        DrawEye(graphics, TransformPoint(mRightEyePosition));
    }
    
}

/**
 * Set the actor using this drawable
 * \param actor Actor using this drawable
 */
void CHeadTop::SetActor(CActor* actor)
{
    CDrawable::SetActor(actor);

    // Set the channel name
    mChannel.SetName(actor->GetName() + L": HeadTop");
}

/** Add the channels for this drawable to a timeline
 * \param timeline The timeline class.
 */
void CHeadTop::SetTimeline(CTimeline* timeline)
{
    CDrawable::SetTimeline(timeline);

    timeline->AddChannel(&mChannel);
}

/** Set the keyframe based on the current status.
*/
void CHeadTop::SetKeyframe()
{
    CDrawable::SetKeyframe();

    mChannel.SetKeyframe(GetPosition());
}

/** Get the current channel from the animation system.
*/
void CHeadTop::GetKeyframe()
{
    CDrawable::GetKeyframe();

    if (mChannel.IsValid())
    {
        SetPosition(mChannel.GetPosition());
    }
}

/** Transform a point from a location on the bitmap to
*  a location on the screen.
* \param  p Point to transform
* \returns Transformed point
*/
Gdiplus::Point CHeadTop::TransformPoint(Gdiplus::Point p)
{
    // Make p relative to the image center
    p = p - GetCenter();

    // Rotate as needed and offset
    return RotatePoint(p, mPlacedR) + mPlacedPosition;
}

/**
* Draws an eyebrow from one point to another point
* Coordinates are based on the head image
* \param graphics Graphics object we are drawing to
* \param point1 1st point for the eyebrow.
* \param point2 2nd point for the eyebrow.
*/
void CHeadTop::DrawEyebrow(Gdiplus::Graphics* graphics, Gdiplus::Point point1, Gdiplus::Point point2)
{
    // Draw the eyebrow
    Pen pen(Color::Black, 2);
    graphics->DrawLine(&pen, point1, point2);
}

/**
* Draws an eye on a given point
* Coordinates are based on the head image
* \param graphics Graphics object we are drawing to
* \param point Point where the eye will be drawn
*/
void CHeadTop::DrawEye(Gdiplus::Graphics* graphics, Gdiplus::Point point)
{
    float wid = 15.0f;
    float hit = 20.0f;
    SolidBrush brush(Color(0, 0, 0));

    auto state = graphics->Save();
    graphics->TranslateTransform(point.X, point.Y);
    graphics->RotateTransform((float)(-mPlacedR * RtoD));
    graphics->FillEllipse(&brush, -wid / 2, -hit / 2, wid, hit);
    graphics->Restore(state);
}
