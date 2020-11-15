/**
 * \file FrisbeeAngleSetter.h
 *
 * \author Reid Harry
 *
 * Visitor for setting the angle of CTowerCustom
 */

#pragma once
#include "ItemVisitor.h"

/** Implements a visitor for setting the angle of CTowerCustom */
class CFrisbeeAngleSetter : public CItemVisitor
{
public:
	/// Constructor
	virtual ~CFrisbeeAngleSetter() {};

	CFrisbeeAngleSetter(CPoint* point);
	virtual void VisitTowerCustom(CTowerCustom* tower);

private:
	/// Point where the CTowerCustom will shoot at
	CPoint* mPoint;
};