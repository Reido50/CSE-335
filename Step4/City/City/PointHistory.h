/**
* \file PointHistory.cpp
*
* \author Charles Owen
*
* Class that maintains a collection of Point objects in order.
*/

#pragma once
#include <memory>
#include <random>


/**
 * Class that maintains a collection of Point objects in order.
 */
class CPointHistory
{
public:
    /// The number of potato lists.
    const static int NumLists = 2;

    CPointHistory();
    virtual ~CPointHistory();

    void Add(Gdiplus::Point p);

protected:
    /// Data is stored in a linked list of data buckets,
    /// where each data bucket is a point and the next 
    /// to the next point in the array of points.

    /**
     * Bucket that stores a single point.
     */
    class PointBucket {
    public:
        Gdiplus::Point mPoint;  ///< Point the bucket is holding
        int mNext = -1;         ///< Next index in the collection
    };

    /// Array containing all available points in buckets.
    std::vector<PointBucket> mPoints;

    /// Array of all available locations in mPoints. 
    std::vector<int> mAvailables;

    /// Index to the first item in the linked list 
    /// of point history. Initially none.
    int mPointFirst = -1;

    /// Index to the last item in the linked list of
    /// point history. Initially none.
    int mPointLast = -1;

    /// Random number generator to use for shuffling
    std::default_random_engine mRandInt;

    /** Iterator
     * Iterator for the point history collection */
    class Iter
    {
    public:
        /** Constructor
         * \param history The point history we are iterating over
         * \param current The current position in the list */
        Iter(CPointHistory* history, int current) : mPointHistory(history), mCurrent(current){
            if (mCurrent != -1)
            {
                mNext = mPointHistory->mPoints[mCurrent].mNext;
            }
        }

        /** Test for end of the iterator
         * \param other Iter object we are comparing against
         * \returns True if this position is not equal to the other position */
        bool operator!=(const Iter& other) const
        {
            return mCurrent != other.mCurrent;
        }

        /** Get value at current position
         * \returns Value at the current bucket */
        Gdiplus::Point operator*() const { return mPointHistory->mPoints[mCurrent].mPoint; }

        /** Increment the iterator
         * \returns Reference to this iterator */
        const Iter& operator++()
        {
            mCurrent = mNext;
            if (mCurrent == -1)
            {
                mNext = -2;
            }
            else
            {
                mNext = mPointHistory->mPoints[mCurrent].mNext;
            }
            return *this;
        }

    private:
        CPointHistory* mPointHistory;           ///< City we are iterating over
        int mCurrent = -1;                      ///< Current bucket position
        int mNext = -2;                         ///< Next bucket position
    };

public:
    /** Get an iterator for the beginning for the collection
     * \returns Iter object at postion 0 */
    Iter begin() { return Iter(this, mPointFirst); }

    /** Get an iterator for the end of the collection
     * \returns Iter object at position past the end */
    Iter end() { return Iter(this, -1); }
};

