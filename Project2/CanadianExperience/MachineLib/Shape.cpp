/**
 * \file Shape.cpp
 *
 * \author Reid Harry
 */

#include "pch.h"
#include "Shape.h"

using namespace std;

/**
* Constructor
*/
CShape::CShape()
{
	mPolygon = make_shared<CPolygon>();
}

/**
* Destructor
*/
CShape::~CShape()
{

}

/**
* Called every frame before the component is drawn
* \param elapsed Time in seconds since last update
*/
void CShape::Update(double elapsed)
{
	
}
