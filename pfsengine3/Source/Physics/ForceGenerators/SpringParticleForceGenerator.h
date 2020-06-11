#pragma once
#include "FixedSpringParticleForceGenerator.h"
// ----------------------------------------------------------------------------
class OParticle;
// ----------------------------------------------------------------------------
class PSpringParticleForceGenerator : public PFixedSpringParticleForceGenerator
{
public:
	PSpringParticleForceGenerator(OParticle* anchor, float springConstant, float restLength);

// PFixedSpringParticleForceGenerator
public:
	virtual void UpdateForce(OParticle* particle, float deltaTime) override;

private:
	OParticle* _anchorParticle;
};
// ----------------------------------------------------------------------------