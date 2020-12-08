/**
 * \file Shape.h
 *
 * \author Reid Harry
 *
 * Basic component that is represented by a polygon
 * Can be a sink
 */

#pragma once

#include "Component.h"
#include "Polygon.h"

/** Basic component that is represented by a polygon */
class CShape :
    public CComponent
{
public:
    CShape();
    /** \brief Copy constructor disabled */
    CShape(const CShape&) = delete;
    /** \brief Assignment operator disabled */
    void operator=(const CShape&) = delete;
    ~CShape();

    void Update(double elapsed);
    std::shared_ptr<CPolygon> GetPolygon();
};

