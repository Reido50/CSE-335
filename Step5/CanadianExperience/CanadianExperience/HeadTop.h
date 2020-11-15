/**
 * \file HeadTop.h
 *
 * \author Reid Harry
 *
 * Drawable class for the top of a stick-figure's head
 */

#pragma once

#include "ImageDrawable.h"

/**
* Drawable class for the top of a stick-figure's head
*/
class CHeadTop :
    public CImageDrawable
{
public:
    CHeadTop(const std::wstring& name, const std::wstring& filename);

    /** \brief Default constructor disabled */
    CHeadTop() = delete;
    /** \brief Copy constructor disabled */
    CHeadTop(const CHeadTop&) = delete;
    /** \brief Assignment operator disabled */
    void operator=(const CHeadTop&) = delete;

    /** Is the top of the head able to be moved 
    * independently of the rest of the actor
    * \returns True */
    virtual bool IsMovable() override { return true; }

    virtual void Draw(Gdiplus::Graphics* graphics) override;

    /** Sets the right eyebrow position
    * \param pos New position of the right eyebrow */
    void SetRightEyebrowPosition(Gdiplus::Point pos) { mRightEyebrowPosition = pos; }

    /** Sets the left eyebrow position
    * \param pos New position of the left eyebrow */
    void SetLeftEyebrowPosition(Gdiplus::Point pos) { mLeftEyebrowPosition = pos; }

    /** Sets the right eye position
    * \param pos New position of the right eye */
    void SetRightEyePosition(Gdiplus::Point pos) { mRightEyePosition = pos; }

    /** Sets the left eye position
    * \param pos New position of the left eye */
    void SetLeftEyePosition(Gdiplus::Point pos) { mLeftEyePosition = pos; }

    /** Get a pointer to the left eye bitmap
     * \returns Pointers to the left eye bitmap
     */
    CRotatedBitmap* GetLeftEye() { return &mLeftEye; }

    /** Get a pointer to the left eye bitmap
     * \returns Pointers to the left eye bitmap
     */
    CRotatedBitmap* GetRightEye() { return &mRightEye; }

private:
    Gdiplus::Point TransformPoint(Gdiplus::Point p);
    void DrawEyebrow(Gdiplus::Graphics* graphics, Gdiplus::Point point1, Gdiplus::Point point2);
    void DrawEye(Gdiplus::Graphics* graphics, Gdiplus::Point point);

    /// Position of the right eyebrow
    Gdiplus::Point mRightEyebrowPosition = Gdiplus::Point(0, 0);

    /// Position of the left eyebrow
    Gdiplus::Point mLeftEyebrowPosition = Gdiplus::Point(0, 0);

    /// Position of the right eye
    Gdiplus::Point mRightEyePosition = Gdiplus::Point(0, 0);

    /// Position of the left eye
    Gdiplus::Point mLeftEyePosition = Gdiplus::Point(0, 0);

    CRotatedBitmap mLeftEye;        ///< Bitmap for the left eye
    CRotatedBitmap mRightEye;       ///< Bitmap for the right eye
};

