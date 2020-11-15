/**
 * \file Item.cpp
 *
 * \author Reid Harry
 */

#include "pch.h"
#include "Item.h"
#include "Aquarium.h"

/**
 * Constuctor
 * \param aquarium The aquarium this item is a member of
 */
CItem::CItem(CAquarium* aquarium) : mAquarium(aquarium)
{
}

/**
 * Destructor
 */
CItem::~CItem()
{
}