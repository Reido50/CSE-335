/**
 * \file MinionFinder.h
 *
 * \author Reid Harry
 *
 * Visitor that finds the minion in the city of a given transporter
 */

#pragma once

#include "TileVisitor.h"
#include "TileTransporter.h"
#include <vector>

/** Visitor class for Finding Minions
 * Visitor that finds the minion in the city of a given transporter */
class CMinionFinder : public CTileVisitor
{
public:
	void VisitTransporter(CTileTransporter* transporter);

	/** Return a shared pointer to the transporter that contains the minion
	 * \returns A shared_ptr to the transporter that contains the minion */
	CTileTransporter* GetMinionLocation() const { return mMinionLocation; }

	/** Return a shared pointer to the transporter that contains the minion
	 * \returns A shared_ptr to the transporter that contains the minion */
	std::vector<CTileTransporter*> GetEmptyTransporters() const { return mEmptyTransporters; }

private:
	/// Transporter that contains the minion
	CTileTransporter* mMinionLocation = nullptr;

	/// Vector of Transporters that do not contains minions
	std::vector<CTileTransporter*> mEmptyTransporters;
};

