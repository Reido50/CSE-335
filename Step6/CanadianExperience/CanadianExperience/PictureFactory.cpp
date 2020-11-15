/**
 * \file PictureFactory.cpp
 *
 * \author Reid Harry
 */

#include "pch.h"
#include "PictureFactory.h"
#include "HaroldFactory.h"
#include "SpartyFactory.h"
#include "ImageDrawable.h"

using namespace std;
using namespace Gdiplus;

/**
* Factory method to create a new picture
* \returns The created picture
*/
std::shared_ptr<CPicture> CPictureFactory::Create()
{
	shared_ptr<CPicture> picture = make_shared<CPicture>();

	// Create the background and add it
	auto background = make_shared<CActor>(L"Background");
	background->SetClickable(false);
	background->SetPosition(Point(-100, 0));
	auto backgroundI =
		make_shared<CImageDrawable>(L"Background", L"images/Background.png");
	background->AddDrawable(backgroundI);
	background->SetRoot(backgroundI);
	picture->AddActor(background);

	// Create and add Harold
	CHaroldFactory haroldFactory;
	auto harold = haroldFactory.Create();

	// Create and add Sparty
	CSpartyFactory spartyFactory;
	auto sparty = spartyFactory.Create();

	// This is where Harold will start out
	harold->SetPosition(Gdiplus::Point(400, 400));
	sparty->SetPosition(Gdiplus::Point(800, 400));

	picture->AddActor(harold);
	picture->AddActor(sparty);

	return picture;
}
