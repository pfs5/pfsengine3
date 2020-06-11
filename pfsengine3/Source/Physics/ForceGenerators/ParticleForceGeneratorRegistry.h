#pragma once
#include "Container/Array.h"
#include "ParticleForceGenerator.h"
// ----------------------------------------------------------------------------
class PRenderTarget;
// ----------------------------------------------------------------------------
class PParticleForceGeneratorRegistry
{
public:
	void UpdateForces(float deltaTime);

	void AddForceGenerator(PParticleForceGenerator* forceGenerator, OParticle* particle);

private:
	struct PForceGeneratorParticlePair
	{
		PParticleForceGenerator* ParticleForceGenerator;
		OParticle* Particle;
	};

	PArray<PForceGeneratorParticlePair> _particleForceGenerators;
};
// ----------------------------------------------------------------------------