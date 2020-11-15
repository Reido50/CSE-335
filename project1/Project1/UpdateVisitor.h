/**
 * \file UpdateVisitor.h
 *
 * \author Jonathan Lee
 *
 * Implementation for visitor called on item updates
 */

#pragma once
#include "ItemVisitor.h"

class CTowerEight;
class CTowerRing;
class CTowerBomb;
class CTowerCustom;
class CBalloon;
class CDart;
class CTileRoad;
class CFrisbee;
class CAnnouncer;
class CBalloonSpawner;

/** Concrete Visitor for Updating Items that move */
class CUpdateVisitor : public CItemVisitor
{
public:
    /// constructor
    CUpdateVisitor(double elapsed);

    /// copy constructor (disabled)
    CUpdateVisitor() = delete;

    /// Destructor
    virtual ~CUpdateVisitor() {}

    virtual void VisitTowerEight(CTowerEight* towerEight) override;

    virtual void VisitTowerRing(CTowerRing* towerRing) override;

    virtual void VisitTowerBomb(CTowerBomb* towerBomb) override;

    virtual void VisitTowerCustom(CTowerCustom* towerCustom) override;

    virtual void VisitBalloon(CBalloon* balloon) override;

    virtual void VisitDart(CDart* dart) override;

    virtual void VisitRoad(CTileRoad* road) override;

    virtual void VisitFrisbee(CFrisbee* frisbee) override;

    virtual void VisitPalette(CMenuPalette* menu) override;

    virtual void VisitAnnouncer(CAnnouncer* mess) override;

    virtual void VisitBalloonSpawner(CBalloonSpawner* spawner) override;

private:
    /// elapsed time
    double mElapsed;
};

