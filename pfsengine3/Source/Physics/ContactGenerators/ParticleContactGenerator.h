#pragma once
#include "../PhysicsShared.h"
#include "Container/Array.h"
// ----------------------------------------------------------------------------
class PParticleContactGenerator
{
public:
	/**
	 * Generate contacts and add to outContacts container. Returns number of generated contacts.
	 */
	virtual int GenerateContacts(PArray<PPhysicsParticleContact>& outContacts) const = 0;
};
// ----------------------------------------------------------------------------