/**
 * \file RotatedBitmap.h
 *
 * \author Reid Harry
 *
 * 
 */

#pragma once

#include <memory>
#include <string>

class CRotatedBitmap
{
public:
    CRotatedBitmap();
    virtual ~CRotatedBitmap();

    /** Copy constructor disabled */
    CRotatedBitmap(const CRotatedBitmap&) = delete;
    /** Assignment operator disabled */
    void operator=(const CRotatedBitmap&) = delete;

    /** Set the center to rotate around
     * \param center New center */
    void SetCenter(Gdiplus::Point center) { mCenter = center; }

    /** Get the center to rotate around
     * \returns Center */
    Gdiplus::Point GetCenter() const { return mCenter; }

    /** Is this bitmap loaded for use?
    * \returns true if loaded */
    bool IsLoaded() const { return mLoaded; }

    void LoadImage(const std::wstring& filename);

    void DrawImage(Gdiplus::Graphics* graphics, Gdiplus::Point position, double angle);

protected:
    /// The image for this drawable
    std::unique_ptr<Gdiplus::Bitmap> mImage;

    /// The center of the image
    Gdiplus::Point mCenter = Gdiplus::Point(0, 0);

    /// Has an image been loaded?
    bool mLoaded = false;
};

