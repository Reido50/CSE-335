/**
 * \file Cable.h
 *
 * \author Reid Harry
 *
 * Represents a cable in the system
 */

#pragma once

class CWinch;

/** Represents a cable in the system */
class CCable
{
public:
    CCable();
    /** \brief Copy constructor disabled */
    CCable(const CCable&) = delete;
    /** \brief Assignment operator disabled */
    void operator=(const CCable&) = delete;
    ~CCable();

    void Draw(Gdiplus::Graphics* graphics, Gdiplus::Point position);
    void Lengthen(double length);
    int GetLength();
    int GetMaxLength();
    void SetWinch(CWinch* winch);
    void SetMinLength(int length);
    void SetMaxLength(int length);
private:
    /// Length of the cable if it didn't have a min and max
    double mVirtualLength = 200;
    /// Current length of the cable
    int mLength = 200;
    /// Maximum length of the cable
    int mMaxLength = 200;
    /// Miniumum length of the cable
    int mMinLength = 20;
    /// Winch the cable belongs to
    CWinch* mWinch = nullptr;
};

