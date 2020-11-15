/**
 * \file MinionTransporter.h
 *
 * \author Reid Harry
 *
 * Visitor that transports a minion to another transporter
 */

#pragma once

#include "TileVisitor.h"
#include "TileTransporter.h"

/** Visitor class for transporting minions
 * Visitor that transports a minon to another transporter */
class CMinionTransporter : public CTileVisitor
{
public:
	/** Constructor
	 * \param city City in which the minion resides */
	CMinionTransporter(CCity* city);

	void VisitTransporter(CTileTransporter* transporter);

private:
	/// The city the minion is in
	CCity* mCity;
};

