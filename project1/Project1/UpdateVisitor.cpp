/**
 * \file UpdateVisitor.cpp
 *
 * \author Jonathan Lee
 */

#include "pch.h"
#include "UpdateVisitor.h"
#include "TowerEight.h"
#include "TowerRing.h"
#include "TowerBomb.h"
#include "TowerCustom.h"
#include "Balloon.h"
#include "Dart.h"
#include "Balloon.h"
#include "TileRoad.h"
#include "Frisbee.h"
#include "MenuPalette.h"
#include "BalloonSpawner.h"

/**
 * Constructor for elapsed time
 * \param elapsed Time we are updating for
 */
CUpdateVisitor::CUpdateVisitor(double elapsed) : CItemVisitor()
{
	mElapsed = elapsed;
}

/**
 * TowerEight visitor
 * \param towerEight Tower we are visiting
 */
void CUpdateVisitor::VisitTowerEight(CTowerEight* towerEight)
{
	towerEight->Update(mElapsed);
}

/**
 * TowerRing visitor
 * \param towerRing Tower we are visiting
 */
void CUpdateVisitor::VisitTowerRing(CTowerRing* towerRing)
{
	towerRing->Update(mElapsed);
}

/**
 * TowerBomb visitor
 * \param towerBomb Tower we are visiting
 */
void CUpdateVisitor::VisitTowerBomb(CTowerBomb* towerBomb)
{
	towerBomb->Update(mElapsed);
}

/**
 * TowerCustom visitor
 * \param towerCustom Tower we are visiting
 */
void CUpdateVisitor::VisitTowerCustom(CTowerCustom* towerCustom)
{
	towerCustom->Update(mElapsed);
}

/**
 * Dart visitor
 * \param dart dart we are visiting
 */
void CUpdateVisitor::VisitDart(CDart* dart)
{
	dart->Update(mElapsed);
}

/**
 * Balloon visitor
 * \param balloon Balloon instance we are visiting
 */
void CUpdateVisitor::VisitBalloon(CBalloon* balloon)
{
	balloon->Update(mElapsed);
}

/**
 * Road visitor
 * \param road Road isntance we are visiting
 */
void CUpdateVisitor::VisitRoad(CTileRoad* road)
{
	road->Update(mElapsed);
}

/**
 * Frisbee visitor
 * \param frisbee Frisbee isntance we are visiting
 */
void CUpdateVisitor::VisitFrisbee(CFrisbee* frisbee)
{
	frisbee->Update(mElapsed);
}

/**
 * Menu visitor
 * \param menu Menu instance we are visiting
 */
void CUpdateVisitor::VisitPalette(CMenuPalette* menu)
{
	menu->Update(mElapsed);
}

/**
 * Announcer visitor
 * \param mess Menu instance we are visiting
 */
void CUpdateVisitor::VisitAnnouncer(CAnnouncer* mess)
{
	mess->Update(mElapsed);
}

/**
 * Balloon Spawner visitor
 * \param spawner Balloon Spawner instance we are visiting
 */
void CUpdateVisitor::VisitBalloonSpawner(CBalloonSpawner* spawner)
{
	spawner->Update(mElapsed);
}