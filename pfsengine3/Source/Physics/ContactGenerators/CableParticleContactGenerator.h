#pragma once
#include "ParticleContactGenerator.h"
// ----------------------------------------------------------------------------
class OParticle;
// ----------------------------------------------------------------------------
class PCableParticleContactGenerator : public PParticleContactGenerator
{
public:
	PCableParticleContactGenerator(OParticle* p1, OParticle* p2, float maxLength, float restitution = 1.f);

// PParticleContactGenerator
public:
	virtual int GenerateContacts(PArray<PPhysicsParticleContact>& outContacts) const override;

private:
	OParticle* _particle1;
	OParticle* _particle2;
	float _maxLength;
	float _restitution;
};
// ----------------------------------------------------------------------------