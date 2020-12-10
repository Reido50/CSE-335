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
	shape1->GetPolygon()->Rectangle(0, 0, 150, 200);
	shape1->GetPolygon()->SetColor(Color::Red);
	shape1->SetPosition(Point(200, 0));

	// Make a cheese
	auto cheese = make_shared<CShape>();
	cheese->GetPolygon()->CenteredSquare(70);
	cheese->GetPolygon()->SetImage(L"images/cheese.png");
	cheese->SetPosition(Point(-300, 0));

	// Make a test mouse
	auto mouse = make_shared<CMouse>();
	mouse->SetPosition(Point(100, 0));
	mouse->SetCheese(cheese);

	// Add components to the assembly
	assembly->AddComponent(shape1);
	assembly->AddComponent(cheese);
	assembly->AddComponent(mouse);

	return assembly;
}
