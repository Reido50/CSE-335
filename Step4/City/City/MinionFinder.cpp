/**
 * \file MinionFinder.cpp
 *
 * \author Reid Harry
 */

#include "pch.h"
#include "MinionFinder.h"
#include "TileTransporter.h"

/** Visitor fuction
 * Visits transporter and determines if it contains a minions 
 * \param transporter Transporter object we are visiting */
void CMinionFinder::VisitTransporter(CTileTransporter* transporter)
{
	if (transporter->GetMinion())
	{
		mMinionLocation = transporter;
	}
	else
	{
		mEmptyTransporters.push_back(transporter);
	}
}