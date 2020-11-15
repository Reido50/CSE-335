/**
 * \file SpartyFactory.cpp
 *
 * \author Reid Harry
 */

#include "pch.h"
#include "SpartyFactory.h"
#include "PolyDrawable.h"
#include "ImageDrawable.h"
#include "HeadTop.h"

using namespace std;
using namespace Gdiplus;

/**
* Creates a sparty actor
* \returns Sparty actor
*/
std::shared_ptr<CActor> CSpartyFactory::Create()
{
    shared_ptr<CActor> actor = make_shared<CActor>(L"Sparty");

    // Make torso
    auto torso = make_shared<CImageDrawable>(L"Torso", L"images/sparty_torso.png");
    torso->SetCenter(Point(69, 144));
    torso->SetPosition(Point(0, -200));
    actor->SetRoot(torso);

    // Make Left Leg
    auto lleg = make_shared<CImageDrawable>(L"Left Leg", L"images/sparty_lleg.png");
    lleg->SetCenter(Point(40, 27));
    lleg->SetPosition(Point(102 - 69, 180 - 144));
    torso->AddChild(lleg);

    // Make Right Leg
    auto rleg = make_shared<CImageDrawable>(L"Right Leg", L"images/sparty_rleg.png");
    rleg->SetCenter(Point(34, 27));
    rleg->SetPosition(Point(36 - 69, 180 - 144));
    torso->AddChild(rleg);

    // Make Bottom of Head
    auto headb = make_shared<CImageDrawable>(L"Head Bottom", L"images/sparty_lhead.png");
    headb->SetCenter(Point(53, 30));
    headb->SetPosition(Point(0, 37 - 144));
    torso->AddChild(headb);

    // Make Top of Head with Face
    auto headt = make_shared<CHeadTop>(L"Head Top", L"images/sparty_head.png");
    headt->SetCenter(Point(59, 143));
    headt->SetPosition(Point(0, -28));
    headb->AddChild(headt);
    headt->GetLeftEye()->LoadImage(L"images/sparty_leye.png");
    headt->GetLeftEye()->SetCenter(Point(-10, -18));
    headt->GetRightEye()->LoadImage(L"images/sparty_reye.png");
    headt->GetRightEye()->SetCenter(Point(48, -18));

    // Make Left Arm
    auto larm = make_shared<CImageDrawable>(L"Left Arm", L"images/sparty_larm.png");
    larm->SetCenter(Point(25, 26));
    larm->SetPosition(Point(120 - 69, 22 - 144));
    torso->AddChild(larm);

    // Make Left Arm
    auto rarm = make_shared<CImageDrawable>(L"Right Arm", L"images/sparty_rarm.png");
    rarm->SetCenter(Point(89, 26));
    rarm->SetPosition(Point(20 - 69, 22 - 144));
    torso->AddChild(rarm);

    // Add drawables in the correct order
    actor->AddDrawable(rleg);
    actor->AddDrawable(lleg);
    actor->AddDrawable(torso);
    actor->AddDrawable(larm);
    actor->AddDrawable(rarm);
    actor->AddDrawable(headb);
    actor->AddDrawable(headt);

    return actor;
}
