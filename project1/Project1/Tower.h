/**
 * \file Tower.h
 *
 * \author Kali Densmore
 *
 * Base class for all tower types to hold common attributes
 */

#pragma once
#include "Item.h"
#include <string>
#include <memory>

 /** Base class for all Towers */
class CTower : public CItem
{
public:
    ///  Default constructor (disabled)
    CTower() = delete;

    ///  Copy constructor (disabled)
    CTower(const CTower&) = delete;

    ~CTower();

    /**  Handle updates for animation
    * \param elapsed The time since the last update
    */
    virtual void Update(double elapsed) override {};

    /**  Determines if the tower has been placed on a tile
    * \returns boolean value of if the tower object is on a tile or not */
    bool HasPlaced() { return mHasPlaced; }

    /**  Placing the tower on a tile, set member variable to be true
    * sets member variable to true indicating the tower was placed
    * \param placed bool of whether the tower was placed.*/
    void SetPlaced(bool placed) { mHasPlaced = placed;  }

    /**  Determines if the tower is on the Palette
    * \returns boolean value of if the tower object is on the palette or not */
    bool OnPalette() { return mOnPalette; }

    /**  Placing the tower on the palette, set member variable to be true
    * sets member variable to true indicating the tower was placed on palette */
    void PlaceOnPalette() { mOnPalette = true; }

    /**
     * Gets grass tile associated with tower
     * \returns shared pointer to grass
     */
    CTileGrass* GetGrass() { return mGrass; }

    /**
     * Sets grass tile associated with tower
     * \param grass Grass tile we are linking
     */
    void SetGrass(CTileGrass* grass) { mGrass = grass; }

protected:

    CTower::CTower(CTowerGame* game, const std::wstring& filename);

private:
    /// Time until tower fires next attack
    double mTimeTillFire = 0;

    /// Indicates if tower is placed on a tile
    bool mHasPlaced = false;

    /// Indicates if tower is placed on the palette
    bool mOnPalette = false;

    /// Grass tile this tower is sitting on
    CTileGrass* mGrass = nullptr;
};

