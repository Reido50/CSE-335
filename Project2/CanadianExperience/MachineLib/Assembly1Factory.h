/**
 * \file Assembly1Factory.h
 *
 * \author Reid Harry
 *
 * Creates the assembly for machine number 1
 */

#pragma once

#include <memory>

class CAssembly;

/** Creates the assembly for machine number 1 */
class CAssembly1Factory
{
public:
	CAssembly1Factory();
	~CAssembly1Factory();

	std::shared_ptr<CAssembly> CreateAssembly();
};

