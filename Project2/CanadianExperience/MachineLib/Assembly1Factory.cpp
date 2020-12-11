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

	// Make a test shape (a red rectangle)
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
	mouse->SetCheese(cheese);

	// Make a test motor
	auto motor = make_shared<CMotor>();
	motor->SetPosition(Point(300, 0));
	motor->SetRotationSpeed(0.01);
	mouse->AddMotor(motor);

	// Make a test gear
	auto gear1 = make_shared<CGear>(70, 20);
	gear1->SetPosition(Point(200, -200));
	gear1->GetPolygon()->SetColor(Color::Purple);

	// Make another test gear
	auto gear2 = make_shared<CGear>(70, 40);
	gear2->SetPosition(Point(200, -400));
	gear2->GetPolygon()->SetColor(Color::BlueViolet);

	// Sources and sinks
	motor->AddSink(gear1);
	gear1->SetSource(motor);
	gear1->AddSink(gear2);
	gear2->SetSource(gear1);
	shape1->SetSource(gear1);
	shape2->SetSource(gear2);
	gear1->AddSink(shape1);
	gear2->AddSink(shape2);

	// Add components to the assembly
	assembly->AddComponent(shape1);
	assembly->AddComponent(shape2);
	assembly->AddComponent(cheese);
	assembly->AddComponent(mouse);
	assembly->AddComponent(motor);
	assembly->AddComponent(gear1);
	assembly->AddComponent(gear2);

	return assembly;
}
