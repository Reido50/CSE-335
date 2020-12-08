/**
 * \file Assembly.h
 *
 * \author Reid Harry
 *
 * Stores all the machine's components
 */

#pragma once

#include <vector>
#include "Component.h"

class CMachineActual;

/** Stores all the machine's components */
class CAssembly
{
public:
    CAssembly();
    /** \brief Copy constructor disabled */
    CAssembly(const CAssembly&) = delete;
    /** \brief Assignment operator disabled */
    void operator=(const CAssembly&) = delete;
    ~CAssembly();

	void Draw(Gdiplus::Graphics* graphics, Gdiplus::Point position);
	void Update(double elapsed);
    void AddComponent(std::shared_ptr<CComponent> component);
    void SetMachine(CMachineActual* machine);
private:
	/// Machine the assembly belongs to
	CMachineActual* mMachine = nullptr;
    /// Components in the machine
    std::vector<std::shared_ptr<CComponent>> mComponents;
};

