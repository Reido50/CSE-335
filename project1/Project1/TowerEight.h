/**
 * \file TowerEight.h
 *
 * \author Kali Densmore
 *
 * Class for tower that shoots eight darts
 */

#pragma once
#include "Item.h"
#include "Tower.h"
#include "TowerGame.h"
#include "XmlNode.h"
#include <memory>
#include "Dart.h"
#include <vector>

 /** Class for Tower Eight */
class CTowerEight : public CTower
{
public:

    CTowerEight(CTowerGame* game);

    ///  Default constructor (disabled)
    CTowerEight() = delete;

    ///  Copy constructor (disabled)
    CTowerEight(const CTowerEight&) = delete;

    /// Default destructor
    ~CTowerEight();

    /** Accept a visitor
    * \param visitor The visitor we accept */
    virtual void Accept(CItemVisitor* visitor) override { visitor->VisitTowerEight(this); }

    /// Function call used to fire the eight darts. 
    void Fire();

    virtual void Update(double elapsed) override;
 
    virtual void Draw(Gdiplus::Graphics* graphics) override;
private:
	
	/// Collection of Darts to fire
	std::vector<std::shared_ptr<CDart>> mDarts;

    /// Decreasing time until next shot
    /// updated in Update() call
    double mTimeTillFire = 5;

    /// Used as reset timer
    const double mTimeBetweenShots = 5;

    /// Clears darts from Tower
    void ClearDarts();
};

