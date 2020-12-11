/**
 * \file Sink.h
 *
 * \author Reid Harry
 *
 * Used to communicate rotation to the sink objects
 */

#pragma once

/** Used to communicate rotation to the sink objects */
class CSink
{
public:
	CSink();
    /** \brief Copy constructor disabled */
    CSink(const CSink&) = delete;
    /** \brief Assignment operator disabled */
    void operator=(const CSink&) = delete;
    ~CSink();

    void Rotate(double rotation);

private:
    double mNetRotation = 0;
};

