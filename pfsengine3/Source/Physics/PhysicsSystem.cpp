#include "ContactGenerators/ParticleContactGenerator.h"
#include "ForceGenerators/ParticleForceGeneratorRegistry.h"
#include "Particle.h"
#include "PhysicsSystem.h"
// ----------------------------------------------------------------------------
PPhysicsSystem& PPhysicsSystem::GetInstance()
{
	static PPhysicsSystem Instance;
	return Instance;
}
// ----------------------------------------------------------------------------
PPhysicsSystem::PPhysicsSystem()
{
	_particleForceRegistry = new PParticleForceGeneratorRegistry();
}
// ----------------------------------------------------------------------------
PPhysicsSystem::~PPhysicsSystem()
{
	delete _particleForceRegistry;
}
// ----------------------------------------------------------------------------
void PPhysicsSystem::Update(float deltaTime)
{
	_particleForceRegistry->UpdateForces(deltaTime);
	ContactGeneratorUpdate(deltaTime);
	ContactResolverUpdate(deltaTime);
}
// ----------------------------------------------------------------------------
void PPhysicsSystem::Draw(PRenderTarget* renderTarget)
{

}
// ----------------------------------------------------------------------------
void PPhysicsSystem::AddForceGenerator(PParticleForceGenerator* forceGenerator, OParticle* particle)
{
	_particleForceRegistry->AddForceGenerator(forceGenerator, particle);
}
// ----------------------------------------------------------------------------
void PPhysicsSystem::AddContactGenerator(PParticleContactGenerator* contactGenerator)
{
	_contactGenerators.Add(contactGenerator);
}
// ----------------------------------------------------------------------------
void PPhysicsSystem::ContactGeneratorUpdate(float deltaTime)
{
	_contacts.Clear(_contacts.Size());

	for (const PParticleContactGenerator* contactGen : _contactGenerators)
	{
		if (contactGen != nullptr)
		{
			contactGen->GenerateContacts(_contacts);
		}
	}
}
// ----------------------------------------------------------------------------
void PPhysicsSystem::ContactResolverUpdate(float deltaTime)
{
	const int maxIterations = _contacts.Size() * 2;
	int iterationsUsed = 0;

	while (iterationsUsed++ < maxIterations)
	{
		float maxSepVelocity = 0.f;
		psize maxIndex = _contacts.Size();
		for (psize i = 0; i < _contacts.Size(); ++i)
		{
			const PPhysicsParticleContact& contact = _contacts[i];
			float sepVelocity = CalculateSeparatingVelocity(contact);
			if (sepVelocity < maxSepVelocity)
			{
				maxSepVelocity = sepVelocity;
				maxIndex = i;
			}
		}

		// nothing to resolve
		if (maxIndex == _contacts.Size())
		{
			break;
		}

		if (_contacts.IsValidIndex(maxIndex))
		{
			ResolveContact(_contacts[maxIndex], deltaTime);
		}
	}
}
// ----------------------------------------------------------------------------
void PPhysicsSystem::ResolveContact(PPhysicsParticleContact& contact, float deltaTime)
{
	ResolveContactVelocity(contact, deltaTime);
	ResolveContactInterpenetration(contact, deltaTime);
}
// ----------------------------------------------------------------------------
void PPhysicsSystem::ResolveContactVelocity(PPhysicsParticleContact& contact, float deltaTime)
{
	if (contact.Particles[0] == nullptr || contact.Particles[1] == nullptr)
	{
		return;
	}

	OParticle* particle1 = contact.Particles[0];
	OParticle* particle2 = contact.Particles[1];

	float separatingVelocity = CalculateSeparatingVelocity(contact);

	// moving away
	if (separatingVelocity > 0)
	{
		return;
	}

	float newSeparatingVelocity = -separatingVelocity * contact.Restitution;
	
	// check velocity buildup due to acceleration (resting contact)
	float accCausedSepVelocity = PVector2::DotProduct(particle1->GetAcceleration() - particle2->GetAcceleration(), contact.ContactNormal) * deltaTime;
	if (accCausedSepVelocity < 0.f)
	{
		newSeparatingVelocity += contact.Restitution * accCausedSepVelocity;	// remove from separating velocity
		newSeparatingVelocity = PMath::Max(0.f, newSeparatingVelocity);			// clamp to zero if negative
	}
	
	float deltaVelocity = newSeparatingVelocity - separatingVelocity;

	float totalInverseMass = particle1->GetInverseMass() + particle2->GetInverseMass();

	// infinite mass = no impulse effect
	if (totalInverseMass <= 0.f)
	{
		return;
	}

	float impulse = deltaVelocity / totalInverseMass;
	PVector2 impulsePerInverseMass = contact.ContactNormal * impulse;

	// Apply impulses - direction of the contact proportional to the inverse mass
	particle1->SetVelocity(particle1->GetVelocity() + impulsePerInverseMass * particle1->GetInverseMass());
	particle2->SetVelocity(particle2->GetVelocity() + impulsePerInverseMass * -particle2->GetInverseMass());
}
// ----------------------------------------------------------------------------
void PPhysicsSystem::ResolveContactInterpenetration(PPhysicsParticleContact& contact, float deltaTime)
{
	if (contact.Particles[0] == nullptr || contact.Particles[1] == nullptr)
	{
		return;
	}

	// no penetration
	if (contact.Penetration <= 0.f)
	{
		return;
	}

	OParticle* particle1 = contact.Particles[0];
	OParticle* particle2 = contact.Particles[1];

	float totalInverseMass = particle1->GetInverseMass() + particle2->GetInverseMass();

	// infinite mass, do nothing
	if (totalInverseMass <= 0.f)
	{
		return;
	}

	PVector2 movePerInverseMass = contact.ContactNormal * (contact.Penetration / totalInverseMass);

	PVector2 particle1Movement = movePerInverseMass * particle1->GetInverseMass();
	PVector2 particle2Movement = movePerInverseMass * -particle2->GetInverseMass();

	particle1->SetPosition(particle1->GetPosition() + particle1Movement);
	particle2->SetPosition(particle2->GetPosition() + particle2Movement);
}
// ----------------------------------------------------------------------------
float PPhysicsSystem::CalculateSeparatingVelocity(const PPhysicsParticleContact& contact)
{
	if (contact.Particles[0] == nullptr)
	{
		return 0.f;
	}

	PVector2 relativeVelocity = contact.Particles[0]->GetVelocity();

	if (contact.Particles[1] != nullptr)
	{
		relativeVelocity -= contact.Particles[1]->GetVelocity();
	}

	return PVector2::DotProduct(relativeVelocity, contact.ContactNormal);
}
// ----------------------------------------------------------------------------