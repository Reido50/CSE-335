/**
 * \file HaroldFactory.cpp
 *
 * \author Reid Harry
 */

#include "pch.h"
#include "HaroldFactory.h"
#include "PolyDrawable.h"
#include "ImageDrawable.h"
#include "HeadTop.h"

using namespace std;
using namespace Gdiplus;

/**
* Creates a Harold actor
* \returns Harold actor
*/
std::shared_ptr<CActor> CHaroldFactory::Create()
{
    shared_ptr<CActor> actor = make_shared<CActor>(L"Harold");

    // Make shirt
    auto shirt = make_shared<CImageDrawable>(L"Shirt", L"images/harold_shirt.png");
    shirt->SetCenter(Point(44, 138));
    shirt->SetPosition(Point(0, -114));
    actor->SetRoot(shirt);

    // Make vest
    auto vest = make_shared<CImageDrawable>(L"Vest", L"images/harold_vest.png");
    vest->SetCenter(Point(44, 138));
    shirt->AddChild(vest);

    // Make Left Leg
    auto lleg = make_shared<CImageDrawable>(L"Left Leg", L"images/harold_lleg.png");
    lleg->SetCenter(Point(11, 9));
    lleg->SetPosition(Point(27, 0));
    shirt->AddChild(lleg);

    // Make Right Leg
    auto rleg = make_shared<CImageDrawable>(L"Right Leg", L"images/harold_rleg.png");
    rleg->SetCenter(Point(39, 9));
    rleg->SetPosition(Point(-27, 0));
    shirt->AddChild(rleg);

    // Make Bottom of Head
    auto headb = make_shared<CImageDrawable>(L"Head Bottom", L"images/harold_headb.png");
    headb->SetCenter(Point(44, 31));
    headb->SetPosition(Point(0, -130));
    shirt->AddChild(headb);

    // Make Top of Head with Face
    auto headt = make_shared<CHeadTop>(L"Head Top with Face", L"images/harold_headt_blank.png");
    headt->SetLeftEyebrowPosition(Point(32, 62));
    headt->SetRightEyebrowPosition(Point(64, 60));
    headt->SetLeftEyePosition(Point(42, 80));
    headt->SetRightEyePosition(Point(69, 80));
    headt->SetCenter(Point(55, 109));
    headt->SetPosition(Point(0, -31));
    headb->AddChild(headt);

    // Make Left Arm
    auto larm = make_shared<CPolyDrawable>(L"Left Arm");
    larm->SetColor(Color(60, 174, 184));
    larm->SetPosition(Point(50, -130));
    larm->AddPoint(Point(-7, -7));
    larm->AddPoint(Point(-7, 96));
    larm->AddPoint(Point(8, 96));
    larm->AddPoint(Point(8, -7));
    shirt->AddChild(larm);

    // Make Right Arm
    auto rarm = make_shared<CPolyDrawable>(L"Right Arm");
    rarm->SetColor(Color(60, 174, 184));
    rarm->SetPosition(Point(-45, -130));
    rarm->AddPoint(Point(-7, -7));
    rarm->AddPoint(Point(-7, 96));
    rarm->AddPoint(Point(8, 96));
    rarm->AddPoint(Point(8, -7));
    shirt->AddChild(rarm);

    // Make Left Hand
    auto lhand = make_shared<CPolyDrawable>(L"Left Hand");
    lhand->SetColor(Color(253, 218, 180));
    lhand->SetPosition(Point(0, 96));
    lhand->AddPoint(Point(-12, -2));
    lhand->AddPoint(Point(-12, 17));
    lhand->AddPoint(Point(11, 17));
    lhand->AddPoint(Point(11, -2));
    larm->AddChild(lhand);

    // Make Right Hand
    auto rhand = make_shared<CPolyDrawable>(L"Right Hand");
    rhand->SetColor(Color(253, 218, 180));
    rhand->SetPosition(Point(0, 96));
    rhand->AddPoint(Point(-12, -2));
    rhand->AddPoint(Point(-12, 17));
    rhand->AddPoint(Point(11, 17));
    rhand->AddPoint(Point(11, -2));
    rarm->AddChild(rhand);

    // Add drawables in the correct order
    actor->AddDrawable(larm);
    actor->AddDrawable(rarm);
    actor->AddDrawable(rhand);
    actor->AddDrawable(lhand);
    actor->AddDrawable(rleg);
    actor->AddDrawable(lleg);
    actor->AddDrawable(shirt);
    actor->AddDrawable(vest);
    actor->AddDrawable(headb);
    actor->AddDrawable(headt);

    return actor;
}