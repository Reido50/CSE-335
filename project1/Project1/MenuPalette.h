/**
 * \file MenuPalette.h
 *
 * \author Jonathan R. Lee
 *
 * Handles Palette on screen
 */

#pragma once
#include "Item.h"
#include "TowerEight.h"
#include "Announcer.h"
#include <memory>

 /** Menu Palette that holds the score */
class CMenuPalette : public CItem
{
public:

	/// Constructor
	CMenuPalette(CTowerGame* towerGame);

	///  Default constructor (disabled)
	CMenuPalette() = delete;

	///  Copy constructor (disabled)
	CMenuPalette(const CMenuPalette&) = delete;

	/// Destructor
	~CMenuPalette();

	void Draw(Gdiplus::Graphics* graphics) override;

	void Update(double elapsed) override;

	/// Visitor acceptor
	/// \param visitor Visitor looking into palette
	virtual void Accept(CItemVisitor* visitor) override { visitor->VisitPalette(this); }

private:
	/// Helper method to update score on board
	std::shared_ptr<CAnnouncer> UpdateScore();

	/// x location of the Menu Palette
	int mX = 0;

	/// y location of the Menu Palette
	int mY = 0;

	/// score announcer to store the score. This will be updated
	std::shared_ptr<CAnnouncer> mScoreAnnouncer;
};

