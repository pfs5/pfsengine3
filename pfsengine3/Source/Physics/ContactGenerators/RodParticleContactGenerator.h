#pragma once
#include "ParticleContactGenerator.h"
// ----------------------------------------------------------------------------
class OParticle;
// ----------------------------------------------------------------------------
class PRodParticleContactGenerator : public PParticleContactGenerator
{
public:
	PRodParticleContactGenerator(OParticle* p1, OParticle* p2, float maxLength);

// PParticleContactGenerator
public:
	virtual int GenerateContacts(PArray<PPhysicsParticleContact>& outContacts) const override;

private:
	OParticle* _particle1;
	OParticle* _particle2;
	float _maxLength;
};
// ----------------------------------------------------------------------------