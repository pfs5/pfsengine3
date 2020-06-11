#pragma once
#include "Math/Vector2.h"
#include "Particle.h"
#include "PhysicsShared.h"
// ----------------------------------------------------------------------------
class PParticleContactGenerator;
class PParticleForceGenerator;
class PParticleForceGeneratorRegistry;
class PRenderTarget;
// ----------------------------------------------------------------------------
class PPhysicsSystem
{
public:
	static PPhysicsSystem& GetInstance();

public:
	PPhysicsSystem();
	~PPhysicsSystem();

	void Update(float deltaTime);
	void Draw(PRenderTarget* renderTarget);

	void AddForceGenerator(PParticleForceGenerator* forceGenerator, OParticle* particle);
	void AddContactGenerator(PParticleContactGenerator* contactGenerator);

private:
	PParticleForceGeneratorRegistry* _particleForceRegistry;
	PArray<PParticleContactGenerator*> _contactGenerators;

	PArray<PPhysicsParticleContact> _contacts;

private:
	void ContactGeneratorUpdate(float deltaTime);
	void ContactResolverUpdate(float deltaTime);

	void ResolveContact(PPhysicsParticleContact& contact, float deltaTime);
	void ResolveContactVelocity(PPhysicsParticleContact& contact, float deltaTime);
	void ResolveContactInterpenetration(PPhysicsParticleContact& contact, float deltaTime);

	float CalculateSeparatingVelocity(const PPhysicsParticleContact& contact);
};
// ----------------------------------------------------------------------------