#include "../Particle.h"
#include "CableParticleContactGenerator.h"
#include "Math/Math.h"
#include "Debug/DebugRenderer.h"
// ----------------------------------------------------------------------------
PCableParticleContactGenerator::PCableParticleContactGenerator(OParticle* p1, OParticle* p2, float maxLength, float restitution/* = 1.f*/):
	_particle1(p1),
	_particle2(p2),
	_maxLength(maxLength),
	_restitution(restitution)
{

}
// ----------------------------------------------------------------------------
int PCableParticleContactGenerator::GenerateContacts(PArray<PPhysicsParticleContact>& outContacts) const
{
	if (_particle1 == nullptr || _particle2 == nullptr)
	{
		return 0;
	}

	PDebugRenderer::GetInstance().DrawDebugLine(_particle1->GetPosition(), _particle2->GetPosition(), 4.f, PColor::Yellow);

	float currentLengthSquared = (_particle2->GetPosition() - _particle1->GetPosition()).SizeSquared();
	if (currentLengthSquared < _maxLength * _maxLength)
	{
		return 0;
	}

	PPhysicsParticleContact contact;
	contact.Particles[0] = _particle1;
	contact.Particles[1] = _particle2;
	contact.ContactNormal = _particle2->GetPosition() - _particle1->GetPosition();
	contact.ContactNormal.Normalize();
	contact.Penetration = PMath::Sqrt(currentLengthSquared) - _maxLength;
	contact.Restitution = _restitution;

	outContacts.Add(contact);

	return 1;
}
// ----------------------------------------------------------------------------