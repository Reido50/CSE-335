/**
 * \file Assembly2Factory.cpp
 *
 * \author Reid Harry
 */

#include "pch.h"
#include "Assembly2Factory.h"
#include "Assembly.h"
#include "Polygon.h"
#include "Shape.h"
#include "Mouse.h"
#include "Motor.h"
#include "Gear.h"
#include "Winch.h"
#include "Pin.h"
#include "Basket.h"

using namespace std;
using namespace Gdiplus;

/**
* Constructor
*/
CAssembly2Factory::CAssembly2Factory()
{

}

/**
* Destructor
*/
CAssembly2Factory::~CAssembly2Factory()
{

}

/**
* Creates and returns the assembly for machine 2
* \returns Created assembly
*/
std::shared_ptr<CAssembly> CAssembly2Factory::CreateAssembly()
{
	// Make the assembly
	auto assembly = make_shared<CAssembly>();

	// Shape for the floor
	auto shape = make_shared<CShape>();
	shape->GetPolygon()->Rectangle(0, 0, 700, 10);
	shape->SetPosition(Point(-350, -10));
	shape->GetPolygon()->SetColor(Color::LightGray);

	// The cheese
	auto cheese = make_shared<CShape>();
	cheese->GetPolygon()->CenteredSquare(70);
	cheese->GetPolygon()->SetImage(L"images/cheese.png");
	cheese->SetPosition(Point(-35, -55));

	// The mouse
	auto mouse = make_shared<CMouse>();
	mouse->SetStart(Point(300, -55));
	mouse->SetCheese(cheese);

	// The post for the gear
	auto post = make_shared<CShape>();
	post->GetPolygon()->Rectangle(0, 0, 12, 100);
	post->SetPosition(Point(-220, -20));
	post->GetPolygon()->SetImage(L"images/post.png");

	// The base of the post for the gear
	auto post_base = make_shared<CShape>();
	post_base->GetPolygon()->Rectangle(0, 0, 50, 50);
	post_base->SetPosition(Point(-240, -13));
	post_base->GetPolygon()->SetImage(L"images/post-base.png");

	// The motor
	auto motor = make_shared<CMotor>();
	motor->GetBody()->SetImage(L"images/motor2.png");
	motor->SetPosition(Point(-280, -70));
	motor->SetRotationSpeed(0.25);
	mouse->AddMotor(motor);

	// First gear
	auto gear1 = make_shared<CGear>(30, 15);
	gear1->GetPolygon()->SetImage(L"images/hammered-copper.png");
	gear1->SetPosition(Point(-280, -70));
	motor->AddSink(gear1);
	gear1->SetSource(motor);

	// Second gear
	auto gear2 = make_shared<CGear>(60, 40);
	gear2->GetPolygon()->SetImage(L"images/steel.png");
	gear2->SetPosition(Point(-215, -125));
	gear1->AddSink(gear2);
	gear2->SetSource(gear1);

	// Third gear
	auto gear3 = make_shared<CGear>(20, 15);
	gear3->GetPolygon()->SetImage(L"images/iron.png");
	gear3->SetPosition(Point(-215, -125));
	gear3->SetStacked(true);
	gear2->AddSink(gear3);
	gear3->SetSource(gear2);

	// Fourth gear
	auto gear4 = make_shared<CGear>(80, 30);
	gear4->GetPolygon()->SetImage(L"images/hammered-copper.png");
	gear4->SetPosition(Point(-155, -200));
	gear4->SetMaxRotation(0.33);
	gear3->AddSink(gear4);
	gear4->SetSource(gear3);

	// Mallet
	auto mallet = make_shared<CShape>();
	mallet->GetPolygon()->Rectangle(-60, 0, 150, 300);
	mallet->GetPolygon()->SetImage(L"images/mallet.png");
	mallet->SetPosition(Point(-155, -200));
	gear4->AddSink(mallet);
	mallet->SetSource(gear4);

	// Add components to the assembly
	assembly->AddComponent(shape);
	assembly->AddComponent(cheese);
	assembly->AddComponent(mouse);
	assembly->AddComponent(post);
	assembly->AddComponent(post_base);
	assembly->AddComponent(motor);
	assembly->AddComponent(gear1);
	assembly->AddComponent(gear2);
	assembly->AddComponent(gear3);
	assembly->AddComponent(gear4);
	assembly->AddComponent(mallet);

	return assembly;
}
