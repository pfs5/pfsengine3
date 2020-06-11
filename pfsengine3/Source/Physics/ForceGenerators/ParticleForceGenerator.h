#pragma once
// ----------------------------------------------------------------------------
class OParticle;
class PRenderTarget;
// ----------------------------------------------------------------------------
class PParticleForceGenerator
{
public:
	virtual void UpdateForce(OParticle* particle, float deltaTime) = 0;
};
// ----------------------------------------------------------------------------