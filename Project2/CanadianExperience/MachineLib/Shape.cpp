/**
 * \file Shape.cpp
 *
 * \author Reid Harry
 */

#include "pch.h"
#include "Shape.h"

using namespace std;

CShape::CShape()
{
	mPolygon = make_shared<CPolygon>();
}

CShape::~CShape()
{

}

void CShape::Update(double elapsed)
{
	
}

std::shared_ptr<CPolygon> CShape::GetPolygon()
{
	return mPolygon;
}
