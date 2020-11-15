/**
 * \file MinionTransporter.cpp
 *
 * \author Reid Harry
 */

#include "pch.h"
#include "MinionTransporter.h"
#include "TileTransporter.h"
#include "MinionFinder.h"
#include <vector>

using namespace std;

CMinionTransporter::CMinionTransporter(CCity* city) : mCity(city) {}

/** Visitor fuction
 * Visits transporter and teleports a minion either to or from it
 * \param transporter Transporter object we are visiting */
void CMinionTransporter::VisitTransporter(CTileTransporter* transporter)
{
	// Visit all transporters
	CMinionFinder visitor;
	mCity->Accept(&visitor);

	if (transporter->GetMinion())
	{
		// Clicked on transporter with minion

		if(!visitor.GetEmptyTransporters().empty())
		{
			// Remove existing minion
			transporter->SetMinion(false);

			// Randomly enable minion on one of the previously empty transporters
			visitor.GetEmptyTransporters()[(rand() % visitor.GetEmptyTransporters().size())]->SetMinion(true);
		}
	}
	else
	{
		// Clicked on an empty transporter
		
		if (visitor.GetMinionLocation() != nullptr)
		{
			// Remove the existing minion
			visitor.GetMinionLocation()->SetMinion(false);

			// Enable minion on the clicked on transporter
			transporter->SetMinion(true);
		}
		
	}
}