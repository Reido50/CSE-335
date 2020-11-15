/**
 * \file Picture.h
 *
 * \author Reid Harry
 *
 * Picture we are drawing
 */

#pragma once

#include <vector>
#include <memory>
#include "Timeline.h"

class CPictureObserver;
class CActor;

/**
* The picture we are drawing.
* 
* There will be one picture object that contains all of
* our actors, which then contains the drawables.
*/
class CPicture
{
public:
	CPicture(){}

	/// Copy Constructor (Disabled)
	CPicture(const CPicture&) = delete;

	/// Assignment Constructor (Disabled)
	void operator=(const CPicture&) = delete;

	/** The picture size
	* \returns Size */
	Gdiplus::Size GetSize() { return mSize; }

	/** The picture size
	* \param size The new picture size */
	void SetSize(Gdiplus::Size size) { mSize = size; }

	/** Get a pointer to the Timeline object
	 * \returns Pointer to the Timeline object
	 */
	CTimeline* GetTimeline() { return &mTimeline; }

	void AddObserver(CPictureObserver* observer);
	void RemoveObserver(CPictureObserver* observer);
	void UpdateObservers();
	void AddActor(std::shared_ptr<CActor>);
	void Draw(Gdiplus::Graphics* graphics);
	void SetAnimationTime(double time);

	/** Iterator that iterates over the actors in this picture */
	class Iter
	{
	public:
		/** Constructor
		* \param picture Picture the iterator is iterating over
		* \param pos Position of the iterator */
		Iter(CPicture* picture, int pos) : mPicture(picture), mPos(pos) {}

		/** Test for end of the iterator
		* \param other Other iterator we care comparing to
		* \returns true if this position is not equal to the other position */
		bool operator!=(const Iter& other) const
		{
			return mPos != other.mPos;
		}

		/** Get value at current position
		* \returns Value at mPos in the collection */
		std::shared_ptr<CActor> operator*() const { return mPicture->mActors[mPos]; }

		/** Increment the iterator
		* \returns Value at mPos in the collection */
		const Iter& operator++()
		{
			mPos++;
			return *this;
		}

	private:
		CPicture* mPicture;	///< Picture we are iterating over
		int mPos;			///< Position in the collection
	};

	/** Get an iterator for the beginning of the collection
	* \returns Iter object at position 0 */
	Iter begin() { return Iter(this, 0); }

	/** Get an iterator for the end of the collection
	* \returns Iter object at position past the end */
	Iter end() { return Iter(this, mActors.size()); }

private:
	/// The picture size
	Gdiplus::Size mSize = Gdiplus::Size(800, 600);

	/// The observers of this picture
	std::vector<CPictureObserver*> mObservers;

	/// The actors in this picture
	std::vector<std::shared_ptr<CActor>> mActors;

	/// The animation timeline
	CTimeline mTimeline;
};

