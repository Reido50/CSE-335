/**
 * \file TileTransporter.h
 *
 * \author Reid Harry
 *
 * Class for the Transporter tile
 */

#pragma once

#include "Tile.h"
#include "City.h"

/** Transporter Tile Class
 * Class for the Transporter tile */
class CTileTransporter : public CTile
{
public:
    CTileTransporter(CCity* city);

    ///  Default constructor (disabled)
    CTileTransporter() = delete;

    ///  Copy constructor (disabled)
    CTileTransporter(const CTileTransporter&) = delete;

    ~CTileTransporter();

    /** Accept a visitor
     * \param visitor The visitor we accept */
    virtual void Accept(CTileVisitor* visitor) override { visitor->VisitTransporter(this); }

    virtual void Draw(Gdiplus::Graphics* graphics) override;

    /** Getter for mMinion 
     * \return True if transporter contains a minion */
    bool GetMinion() { return mMinion; }

    /** Setter for mMinion
     * \param minion The value to set mMinion to */
    void SetMinion(bool minion) { mMinion = minion; }

private:
    /// The image of a minion
    std::unique_ptr<Gdiplus::Bitmap> mMinionImage;

    /// True if a minion should be draw on this tile
    boolean mMinion = false;
};

