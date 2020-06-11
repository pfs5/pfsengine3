#include "../Particle.h"
#include "Debug/DebugRenderer.h"
#include "Math/Math.h"
#include "RodParticleContactGenerator.h"
// ----------------------------------------------------------------------------
PRodParticleContactGenerator::PRodParticleContactGenerator(OParticle* p1, OParticle* p2, float maxLength):
	_particle1(p1),
	_particle2(p2),
	_maxLength(maxLength)
{

}
// ----------------------------------------------------------------------------
int PRodParticleContactGenerator::GenerateContacts(PArray<PPhysicsParticleContact>& outContacts) const
{
	if (_particle1 == nullptr || _particle2 == nullptr)
	{
		return 0;
	}

	PDebugRenderer::GetInstance().DrawDebugLine(_particle1->GetPosition(), _particle2->GetPosition(), 4.f, PColor::Cyan);

	float currentLengthSquared = (_particle2->GetPosition() - _particle1->GetPosition()).SizeSquared();
	if (PMath::IsNearlyEqual(currentLengthSquared, _maxLength * _maxLength))
	{
		return 0;
	}

	float currentLength = PMath::Sqrt(currentLengthSquared);

	PVector2 normal = _particle2->GetPosition() - _particle1->GetPosition();
	normal.Normalize();

	PPhysicsParticleContact contact;
	contact.Particles[0] = _particle1;
	contact.Particles[1] = _particle2;
	contact.ContactNormal = currentLength > _maxLength ? normal : -normal;
	contact.Penetration = currentLength > _maxLength ? currentLength - _maxLength : _maxLength - currentLength;
	contact.Restitution = 0.f;	// no bounciness

	outContacts.Add(contact);

	return 1;
}
// ----------------------------------------------------------------------------