/**
 * \file Assembly1Factory.cpp
 *
 * \author Reid Harry
 */

#include "pch.h"
#include "Assembly1Factory.h"
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

CAssembly1Factory::CAssembly1Factory()
{

}

CAssembly1Factory::~CAssembly1Factory()
{

}

std::shared_ptr<CAssembly> CAssembly1Factory::CreateAssembly()
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

	// The trap stand
	auto stand = make_shared<CShape>();
	stand->GetPolygon()->CenteredSquare(300);
	stand->GetPolygon()->SetImage(L"images/trap-stand.png");
	stand->SetPosition(Point(0, -160));

	// The trap stand front
	auto front = make_shared<CShape>();
	front->GetPolygon()->CenteredSquare(300);
	front->GetPolygon()->SetImage(L"images/trap-stand-front.png");
	front->SetPosition(Point(0, -160));

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
	gear1->GetPolygon()->SetImage(L"images/iron.png");
	gear1->SetPosition(Point(-280, -70));
	motor->AddSink(gear1);
	gear1->SetSource(motor);

	// Second gear
	auto gear2 = make_shared<CGear>(60, 40);
	gear2->GetPolygon()->SetImage(L"images/hammered-copper.png");
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
	auto gear4 = make_shared<CGear>(80, 48);
	gear4->GetPolygon()->SetImage(L"images/steel.png");
	gear4->SetPosition(Point(-285, -190));
	gear3->AddSink(gear4);
	gear4->SetSource(gear3);

	// Fifth gear
	auto gear5 = make_shared<CGear>(15, 12);
	gear5->GetPolygon()->SetImage(L"images/iron.png");
	gear5->SetPosition(Point(-285, -190));
	gear5->SetStacked(true);
	gear4->AddSink(gear5);
	gear5->SetSource(gear4);

	// Sixth gear
	auto gear6 = make_shared<CGear>(50, 40);
	gear6->GetPolygon()->SetImage(L"images/hammered-copper.png");
	gear6->SetPosition(Point(-250, -240));
	gear5->AddSink(gear6);
	gear6->SetSource(gear5);

	// Winch
	auto winch = make_shared<CWinch>();
	winch->SetPosition(Point(-250, -240));
	gear6->AddSink(winch);
	winch->SetSource(gear6);

	// Pin
	auto pin = make_shared<CPin>();
	pin->SetPosition(Point(0, -160));
	pin->SetCable(winch->GetCable());

	// Basket
	auto basket = make_shared<CBasket>();
	basket->SetPosition(Point(0, -160));
	basket->SetStart(Point(0, -160));
	pin->SetBasket(basket);
	basket->SetPin(pin);

	// Add components to the assembly
	assembly->AddComponent(shape);
	assembly->AddComponent(cheese);
	assembly->AddComponent(mouse);
	assembly->AddComponent(stand);
	//add basket here
	assembly->AddComponent(front);
	assembly->AddComponent(post);
	assembly->AddComponent(post_base);
	assembly->AddComponent(motor);
	assembly->AddComponent(gear1);
	assembly->AddComponent(gear2);
	assembly->AddComponent(gear3);
	assembly->AddComponent(gear4);
	assembly->AddComponent(gear5);
	assembly->AddComponent(gear6);
	assembly->AddComponent(winch);
	assembly->AddComponent(pin);
	assembly->AddComponent(basket);

	/*// Make a test shape (a red rectangle)
	auto shape1 = make_shared<CShape>();
	shape1->GetPolygon()->Rectangle(0, 0, 20, 80);
	shape1->GetPolygon()->SetColor(Color::Red);
	shape1->SetPosition(Point(450, 0));

	// Make a test shape (a red rectangle)
	auto shape2 = make_shared<CShape>();
	shape2->GetPolygon()->Rectangle(0, 0, 20, 80);
	shape2->GetPolygon()->SetColor(Color::DarkOrange);
	shape2->SetPosition(Point(450, 0));

	// Make a cheese
	auto cheese = make_shared<CShape>();
	cheese->GetPolygon()->CenteredSquare(70);
	cheese->GetPolygon()->SetImage(L"images/cheese.png");
	cheese->SetPosition(Point(-300, 0));

	// Make a test mouse
	auto mouse = make_shared<CMouse>();
	mouse->SetPosition(Point(100, 0));
	mouse->SetStart(Point(100, 0));
	mouse->SetCheese(cheese);

	// Make a test motor
	auto motor = make_shared<CMotor>();
	motor->SetPosition(Point(300, 0));
	motor->SetRotationSpeed(0.25);
	mouse->AddMotor(motor);
	motor->SetOn(true);

	// Make a test gear
	auto gear1 = make_shared<CGear>(70, 20);
	gear1->SetPosition(Point(200, -200));
	gear1->GetPolygon()->SetColor(Color::Purple);

	// Make another test gear
	auto gear2 = make_shared<CGear>(70, 40);
	gear2->SetPosition(Point(200, -400));
	gear2->GetPolygon()->SetColor(Color::BlueViolet);

	// Make a test winch
	auto winch = make_shared<CWinch>();
	winch->SetPosition(Point(-200, -400));

	// Make a test pin
	auto pin = make_shared<CPin>();
	pin->SetPosition(Point(0, -318));
	pin->SetCable(winch->GetCable());

	// Make a test basket
	auto basket = make_shared<CBasket>();
	basket->SetPosition(Point(0, -464));
	basket->SetPin(pin);
	pin->SetBasket(basket);

	// Sources and sinks
	motor->AddSink(gear1);
	gear1->SetSource(motor);
	gear1->AddSink(gear2);
	gear2->SetSource(gear1);
	shape1->SetSource(gear1);
	shape2->SetSource(gear2);
	gear1->AddSink(shape1);
	gear2->AddSink(shape2);
	winch->SetSource(winch);
	gear2->AddSink(winch);

	// Add components to the assembly
	assembly->AddComponent(shape1);
	assembly->AddComponent(shape2);
	assembly->AddComponent(cheese);
	assembly->AddComponent(mouse);
	assembly->AddComponent(motor);
	assembly->AddComponent(gear1);
	assembly->AddComponent(gear2);
	assembly->AddComponent(winch);
	assembly->AddComponent(pin);
	assembly->AddComponent(basket);*/

	return assembly;
}
