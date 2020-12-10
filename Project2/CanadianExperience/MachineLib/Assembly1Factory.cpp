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

	// Make a test shape (a green rectangle)
	auto shape2 = make_shared<CShape>();
	shape2->GetPolygon()->Rectangle(0, 0, 100, 200);
	shape2->GetPolygon()->SetColor(Color::Green);
	shape2->SetPosition(Point(0, 0));

	// Make a test mouse
	auto mouse = make_shared<CMouse>();
	mouse->SetPosition(Point(200, 200));

	// Add components to the assembly
	assembly->AddComponent(shape1);
	assembly->AddComponent(shape2);
	assembly->AddComponent(mouse);

	return assembly;
}
