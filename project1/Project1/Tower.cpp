/**
 * \file Tower.cpp
 *
 * \author Kali Densmore
 */

#include "pch.h"
#include "Tower.h"

using namespace std;
using namespace Gdiplus;

/** Constructor
* \param game The Game this is a member of
* \param filename File of the tower image
*/
CTower::CTower(CTowerGame* game, const std::wstring& filename) : CItem(game, filename)
{
}


/**
*  Destructor
*/
CTower::~CTower()
{
}

