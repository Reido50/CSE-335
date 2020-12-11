/**
 * \file Source.h
 *
 * \author Reid Harry
 *
 * Used to communicate rotation to sinks
 */

#pragma once

/** Used to communicate rotation to sinks */
class CSource
{
public:
    CSource();
    /** \brief Copy constructor disabled */
    CSource(const CSource&) = delete;
    /** \brief Assignment operator disabled */
    void operator=(const CSource&) = delete;
    ~CSource();

    void RotateSinks(double rotation, int numTeeth = 0);
};

