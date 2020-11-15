/**
 * \file PictureObserver.cpp
 *
 * \author Reid Harry
 */

#include "pch.h"
#include "PictureObserver.h"
#include "Picture.h"

 /**
 * Destructor
 *
 * Must be declared as virtual:
 * virtual ~CPictureObserver();
 */
CPictureObserver::~CPictureObserver()
{
	if (mPicture != nullptr)
	{
		mPicture->RemoveObserver(this);
	}
}

/** The observed picture
* \param picture The new picture to be observed */
void CPictureObserver::SetPicture(std::shared_ptr<CPicture> picture)
{
	mPicture = picture;
	mPicture->AddObserver(this);
}