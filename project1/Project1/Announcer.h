/**
 * \file Announcer.h
 *
 * \author Jonathan Lee
 *
 * Base class to display text on screen.
 */

#pragma once
#include "Item.h"
#include <string>

 /** Base class for the announcer messages */
class CAnnouncer : public CItem
{
public:
	/// Default constructor disabled
	CAnnouncer() = delete;

	/// Copy Constructor
	CAnnouncer(const CAnnouncer&) = delete;

	/// Destructor
	~CAnnouncer();

	/// Base constructor to display messages
	CAnnouncer(CTowerGame* towerGame, std::wstring message, int colorA, int colorB, int colorC);

	/**
	 * Draw function override
	 * \param graphics Graphics system we draw to
	 */
	virtual void Draw(Gdiplus::Graphics* graphics) override;

	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CItemVisitor* visitor) override;

protected:
	/// Font size of the announcement
	int mFontSize;

	/// Actual message to display
	std::wstring mMessage;
private:

	/// First color to contribute to the final color of announcement
	int mColorA;

	/// Second color to contribute to the final color of announcement
	int mColorB;

	/// Third color to contribute to the final color of announcement
	int mColorC;

};

