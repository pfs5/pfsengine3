#include "ParticleForceGeneratorRegistry.h"
// ----------------------------------------------------------------------------
void PParticleForceGeneratorRegistry::UpdateForces(float deltaTime)
{
	for (const PForceGeneratorParticlePair& forceGeneratorPair : _particleForceGenerators)
	{
		forceGeneratorPair.ParticleForceGenerator->UpdateForce(forceGeneratorPair.Particle, deltaTime);
	}
}
// ----------------------------------------------------------------------------
void PParticleForceGeneratorRegistry::AddForceGenerator(PParticleForceGenerator* forceGenerator, OParticle* particle)
{
	_particleForceGenerators.Add(PForceGeneratorParticlePair{forceGenerator, particle});
}
// ----------------------------------------------------------------------------