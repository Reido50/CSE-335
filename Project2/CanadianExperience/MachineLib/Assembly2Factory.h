/**
 * \file Assembly2Factory.h
 *
 * \author Reid Harry
 *
 * Creates the assembly for machine 2
 */

#pragma once

#include <memory>

class CAssembly;

/** Creates the assembly for machine 2 */
class CAssembly2Factory
{
public:
	CAssembly2Factory();
	~CAssembly2Factory();

	std::shared_ptr<CAssembly> CreateAssembly();
};

