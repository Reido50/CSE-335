/**
 * \file PictureFactory.cpp
 *
 * \author Charles B. Owen
 */

#include "pch.h"
#include "PictureFactory.h"
#include "HaroldFactory.h"
#include "SpartyFactory.h"
#include "ImageDrawable.h"
#include "MachineDrawable.h"

using namespace std;
using namespace Gdiplus;

CPictureFactory::CPictureFactory()
{
}


CPictureFactory::~CPictureFactory()
{
}


/*! Factory method to create a new picture.
* \returns The created picture
*/
std::shared_ptr<CPicture> CPictureFactory::Create()
{
    shared_ptr<CPicture> picture = make_shared<CPicture>();

    // Create the background and add it
    auto background = make_shared<CActor>(L"Background");
    background->SetClickable(false);
    background->SetPosition(Point(-100, 0));
    auto backgroundI = make_shared<CImageDrawable>(L"Background", L"images/Background.png");
    background->AddDrawable(backgroundI);
    background->SetRoot(backgroundI);
    picture->AddActor(background);

    // Create and add machine
    auto machine1 = make_shared<CActor>(L"Machine Actor");
    auto machineDrawable1 = make_shared<CMachineDrawable>(L"Machine Drawable", 1);
    machineDrawable1->SetPosition(Point(1500, 1000));
    machineDrawable1->SetScale(0.5);
    machine1->AddDrawable(machineDrawable1);
    machine1->SetRoot(machineDrawable1);
    picture->AddActor(machine1);

    // Create and add machine
    auto machine2 = make_shared<CActor>(L"Machine Actor");
    auto machineDrawable2 = make_shared<CMachineDrawable>(L"Machine Drawable", 2);
    machineDrawable2->SetPosition(Point(500, 1000));
    machineDrawable2->SetScale(0.5);
    machine2->AddDrawable(machineDrawable2);
    machine2->SetRoot(machineDrawable2);
    picture->AddActor(machine2);

    // Create and add Harold
    CHaroldFactory factory;
    auto harold = factory.Create();

    // This is where Harold will start out.
    harold->SetPosition(Point(750, 500));

    picture->AddActor(harold);

    // Create and add Sparty
    CSpartyFactory sfactory;
    auto sparty = sfactory.Create();

    sparty->SetPosition(Point(520, 500));
    picture->AddActor(sparty);

    return picture;
}
