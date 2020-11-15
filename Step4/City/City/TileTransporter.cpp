/**
 * \file TileTransporter.cpp
 *
 * \author Reid Harry
 */

#include "pch.h"
#include "TileTransporter.h"
#include "MinionFinder.h"
#include "City.h"
#include "Tile.h"

using namespace std;
using namespace Gdiplus;

/** Constructor
* \param city The city this is a member of
*/
CTileTransporter::CTileTransporter(CCity* city) : CTile(city)
{
    mMinionImage = unique_ptr<Bitmap>(Bitmap::FromFile(L"images/transporter-minion.png"));
    if (mMinionImage->GetLastStatus() != Ok)
    {
        wstring msg(L"Failed to open ");
        msg += L"transporter-minion.png";
        AfxMessageBox(msg.c_str());
        return;
    }

    CMinionFinder visitor;
    city->Accept(&visitor);
    if (visitor.GetMinionLocation() == nullptr)
    {
        mMinion = true;
    }
}

/**
*  Destructor
*/
CTileTransporter::~CTileTransporter()
{
}

/**
 * Override of CTile::Draw
 * Accounts for drawing the minion on top
 * of the transporter.
 * \param graphics Graphics we are drawing to
 **/
void CTileTransporter::Draw(Gdiplus::Graphics* graphics)
{
    CTile::Draw(graphics);
    if (mMinionImage != nullptr && mMinion)
    {
        int wid = mMinionImage->GetWidth();
        int hit = mMinionImage->GetHeight();

        graphics->DrawImage(mMinionImage.get(),
            GetX() - OffsetLeft, GetY() + OffsetDown - hit,
            wid, hit);
    }
}