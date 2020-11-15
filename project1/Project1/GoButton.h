/**
 * \file GoButton.h
 *
 * \author Jonathan Lee
 *
 * Contains implementation for starting a game
 */

#pragma once
#include "Item.h"

/** Class for the Go Button in the lower right corner of the game */
class CGoButton : public CItem
{
public:
    /// Constructor
    CGoButton(CTowerGame* game);

    ///  Default constructor (disabled)
    CGoButton() = delete;

    ///  Copy constructor (disabled)
    CGoButton(const CGoButton&) = delete;

    /// Destructor
    ~CGoButton();

    /** Accept a visitor
    * \param visitor The visitor we accept */
    virtual void Accept(CItemVisitor* visitor) override { visitor->VisitGoButton(this); }

    virtual bool HitTest(int x, int y) override;
};

