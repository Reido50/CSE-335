/**
 * \file PolyDrawable.cpp
 *
 * \author Reid Harry
 */

#include "pch.h"
#include "PolyDrawable.h"

using namespace std;
using namespace Gdiplus;

/**
* Constructor
* \param name The drawable name
*/
CPolyDrawable::CPolyDrawable(const std::wstring& name) : CDrawable(name)
{
}

/**
* Draw this drawable
* \param graphics The Graphics object we are drawing on
*/
void CPolyDrawable::Draw(Gdiplus::Graphics* graphics)
{
    SolidBrush brush(mColor);

    // Transform the points
    vector<Point> points;
    for (auto point : mPoints)
    {
        points.push_back(RotatePoint(point, mPlacedR) + mPlacedPosition);
    }

    graphics->FillPolygon(&brush, &points[0], (int)points.size());
}

/**
* Test to see if a mouse click is on this drawable
* \param pos Point of the mouse click
* \returns True if the mouse click was on this drawable
*/
bool CPolyDrawable::HitTest(Gdiplus::Point pos)
{
    // Transform the points
    vector<Point> points;
    for (auto point : mPoints)
    {
        points.push_back(RotatePoint(point, mPlacedR) + mPlacedPosition);
    }

    GraphicsPath path;
    path.AddPolygon(&points[0], (int)points.size());
    return path.IsVisible(pos) ? true : false;
}

/**
* Adds a point to the polygon
* \param point Point to add
*/
void CPolyDrawable::AddPoint(Gdiplus::Point point)
{
	mPoints.push_back(point);
}
