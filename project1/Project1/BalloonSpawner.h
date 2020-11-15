/**
 * \file BalloonSpawner.h
 *
 * \author Jonathan Lee
 *
 * Main class to generate balloons at start of level
 */

#pragma once
#include "Item.h"
#include <memory>

 /** Baloon Spawner that generates balloons at level start */
class CBalloonSpawner : public CItem
{
public:
    /// Default constructor (disabled)
    CBalloonSpawner() = delete;

    /// Copy (disabled)
    CBalloonSpawner(const CBalloonSpawner&) = delete;

    /// Destructor
    ~CBalloonSpawner();

    CBalloonSpawner(CTowerGame* towerGame);

    /// Visitor accept method
    /// \param visitor Visitor isntance we accept
    virtual void Accept(CItemVisitor* visitor) override { visitor->VisitBalloonSpawner(this); };

    /// Main logic override for spawner
    /// \param elapsed Time since last update
    virtual void Update(double elapsed) override;

private:
    /// Last ballon instance we spawned
    std::shared_ptr<CBalloon> mLastSpawned = nullptr;

    /// The number of balloons spawned by this instance
    int mNumSpawned = 0;

    /// Calculates what balloon we are spawning
    void SpawnBalloon();

    /// Delay between last balloon and Owen
    double mOwenDelay = 4.0;
};

