/**
 * \file PolyDrawable.h
 *
 * \author Reid Harry
 *
 * A drawable based on polygon images
 */

#pragma once

#include <vector>
#include "Drawable.h"

/**
* A drawable based on polygon images
* 
* This class had a list of points and draws a polygon
* drawable based on those points.
*/
class CPolyDrawable :
    public CDrawable
{
public:
    CPolyDrawable(const std::wstring& name);

    /** \brief Default constructor disabled */
    CPolyDrawable() = delete;
    /** \brief Copy constructor disabled */
    CPolyDrawable(const CPolyDrawable&) = delete;
    /** \brief Assignment operator disabled */
    void operator=(const CPolyDrawable&) = delete;

    /** Get the PolyDrawable color
    * \returns Color of the PolyDrawable */
    Gdiplus::Color GetColor() { return mColor; }

    /** Set the PolyDrawable color
    * \param color New color from the PolyDrawable */
    void SetColor(Gdiplus::Color color) { mColor = color; }

    void Draw(Gdiplus::Graphics* graphics) override;
    bool HitTest(Gdiplus::Point pos) override;
    void AddPoint(Gdiplus::Point point);

private:
    /// The polygon color
    Gdiplus::Color mColor = Gdiplus::Color::Black;

    /// The array of point objects
    std::vector<Gdiplus::Point> mPoints;
};

