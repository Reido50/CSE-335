/**
 * \file Picture.cpp
 *
 * \author Reid Harry
 */

#include "pch.h"
#include "Picture.h"
#include "PictureObserver.h"
#include "Actor.h"

using namespace Gdiplus;

/**
* Add an observer to this picture
* \param observer The observer to add
*/
void CPicture::AddObserver(CPictureObserver* observer)
{
	mObservers.push_back(observer);
}

/**
* Remove an observer from this picture
* \param observer The observer to remove
*/
void CPicture::RemoveObserver(CPictureObserver* observer)
{
	auto loc = find(std::begin(mObservers), std::end(mObservers), observer);
	if (loc != std::end(mObservers))
	{
		mObservers.erase(loc);
	}
}

/**
* Update all observers to indicate the picture has changed
*/
void CPicture::UpdateObservers()
{
	for (auto observer : mObservers)
	{
		observer->UpdateObserver();
	}
}

/**
* Add an actor to the picture
* \param actor Actor to be added to the picture
*/
void CPicture::AddActor(std::shared_ptr<CActor> actor)
{
	mActors.push_back(actor);
	actor->SetPicture(this);
}

/**
* Draw this picture on a device context
* \param graphics The device context to draw on
*/
void CPicture::Draw(Gdiplus::Graphics* graphics)
{
	for (auto actor : mActors)
	{
		actor->Draw(graphics);
	}
}

/** Set the current animation time
 *
 * This forces the animation of all
 * objects to the current animation location.
 * \param time The new time.
 */
void CPicture::SetAnimationTime(double time)
{
	mTimeline.SetCurrentTime(time);

	for (auto actor : mActors)
	{
		actor->GetKeyframe();
	}

	UpdateObservers();
}