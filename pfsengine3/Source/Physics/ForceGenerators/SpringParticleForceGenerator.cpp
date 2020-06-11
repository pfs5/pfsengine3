#include "../Particle.h"
#include "SpringParticleForceGenerator.h"
// ----------------------------------------------------------------------------
PSpringParticleForceGenerator::PSpringParticleForceGenerator(OParticle* anchor, float springConstant, float restLength):
	PFixedSpringParticleForceGenerator(PVector2::ZeroVector, springConstant, restLength),
	_anchorParticle(anchor)
{

}
// ----------------------------------------------------------------------------
void PSpringParticleForceGenerator::UpdateForce(OParticle* particle, float deltaTime)
{
	if (_anchorParticle != nullptr)
	{
		SetAnchor(_anchorParticle->GetPosition());
	}

	PFixedSpringParticleForceGenerator::UpdateForce(particle, deltaTime);
}
// ----------------------------------------------------------------------------