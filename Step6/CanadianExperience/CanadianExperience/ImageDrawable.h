/**
 * \file ImageDrawable.h
 *
 * \author Reid Harry
 *
 * Drawable class for bitmap images
 */

#pragma once

#include "Drawable.h"
#include "RotatedBitmap.h"

/**
* Drawable class for bitmap images
*/
class CImageDrawable :
    public CDrawable, public CRotatedBitmap
{
public:
    CImageDrawable(const std::wstring& name, const std::wstring& filename);

    /** \brief Default constructor disabled */
    CImageDrawable() = delete;
    /** \brief Copy constructor disabled */
    CImageDrawable(const CImageDrawable&) = delete;
    /** \brief Assignment operator disabled */
    void operator=(const CImageDrawable&) = delete;

    void Draw(Gdiplus::Graphics* graphics) override;
    bool HitTest(Gdiplus::Point point) override;
};

