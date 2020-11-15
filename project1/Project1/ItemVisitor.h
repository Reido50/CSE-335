/**
 * \file ItemVisitor.h
 *
 * \author Jonathan Lee
 *
 * Base class for item visitor implementation
 */

#pragma once
class CTileGrass;
class CTileRoad;
class CTileBuilding;
class CTileTrees;
class CTowerEight;
class CTowerRing;
class CTowerCustom;
class CTowerBomb;
class CBalloon;
class CDart;
class CFrisbee;
class CMenuPalette;
class CGoButton;
class CAnnouncer;
class CBalloonSpawner;

/** Base class for all item visitors */
class CItemVisitor
{
public:
    /**
    * Destructor
    */
	virtual ~CItemVisitor() {}

    /** Visit a CTileBuilding object
     *  \param building Building we are visiting */
    virtual void VisitBuilding(CTileBuilding* building) {}

    /** Visit a CTileGrass object
     *  \param grass Grass tile we are visiting */
    virtual void VisitGrass(CTileGrass* grass) {}

    /** Visit a CTileTrees object
     *  \param trees Trees tile we are visiting */
    virtual void VisitTrees(CTileTrees* trees) {}

    /** Visit a CTileRoad object
     *  \param road Road we are visiting */
    virtual void VisitRoad(CTileRoad* road) {}

    /** Visit a CTowerEight object
     *  \param towereight Tower Eight we are visiting */
    virtual void VisitTowerEight(CTowerEight* towereight) {}

    /** Visit a CTowerRing object
     *  \param towerring Ring Tower we are visiting */
    virtual void VisitTowerRing(CTowerRing* towerring) {}

    /** Visit a CTowerCustom object
     *  \param towerbomb Bomb Tower we are visiting */
    virtual void VisitTowerBomb(CTowerBomb* towerbomb) {}

    /** Visit a CTowerCustom object
     *  \param towercustom Custom Tower we are visiting */
    virtual void VisitTowerCustom(CTowerCustom* towercustom) {}

    /** Visit a CBalloon object
     *  \param balloon Balloon item we are visiting */
    virtual void VisitBalloon(CBalloon* balloon) {}

    /** Visit a CDart object
     *  \param dart Dart item we are visiting */
    virtual void VisitDart(CDart* dart) {}

    /** Visit a CFrisbee object
     *  \param frisbee Frisbee item we are visiting */
    virtual void VisitFrisbee(CFrisbee* frisbee) {}

    /** Visit a CMenuPalette object
    *  \param menu Menu item we are visiting */
    virtual void VisitPalette(CMenuPalette* menu) {}

    /** Visit a CGoButton object
     *  \param button Go Button item we are visiting */
    virtual void VisitGoButton(CGoButton* button) {}

    /** Visit a CAnnouncer object
     *  \param announcer Announcer item we are visiting */
    virtual void VisitAnnouncer(CAnnouncer* announcer) {}

    /** Visit a CBalloonSpawner object
     *  \param spawner Balloon Spawner item we are visiting */
    virtual void VisitBalloonSpawner(CBalloonSpawner* spawner) {}
};

