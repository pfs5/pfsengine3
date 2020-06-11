#include "Container/PFSEngineColor.h"
#include "Debug/DebugRenderer.h"
#include "FixedSpringParticleForceGenerator.h"
#include "Math/Math.h"
#include "Physics/Particle.h"
#include "Rendering/PFSEngineWindow.h"
#include "Logging/DebugLog.h"
// ----------------------------------------------------------------------------
PFixedSpringParticleForceGenerator::PFixedSpringParticleForceGenerator(const PVector2& anchor, float springConstant, float restLength):
	_anchor(anchor),
	_springConstant(springConstant),
	_restLength(restLength)
{

}
// ----------------------------------------------------------------------------
void PFixedSpringParticleForceGenerator::SetAnchor(const PVector2& anchor)
{
	_anchor = anchor;
}
// ----------------------------------------------------------------------------
void PFixedSpringParticleForceGenerator::UpdateForce(OParticle* particle, float deltaTime)
{
	if (particle == nullptr)
	{
		return;
	}

	PVector2 force = particle->GetPosition() - _anchor;
	float forceSize = force.Size();
	float magnitude = (_restLength - forceSize) * _springConstant;

	if (!PMath::IsNearlyZero(forceSize))
	{
		force /= forceSize;
	}
	force *= magnitude;

	particle->AddForce(force);

	float colorDist = PMath::Abs((particle->GetPosition() - _anchor).Size() - _restLength);
	float colorFactor = colorDist / _restLength;
	float colorK = 0.f;
	if (colorFactor < 1.f) colorK = 0.f;
	else if (colorFactor < 2.f) colorK = 0.25f;
	else if (colorFactor < 3.f) colorK = 0.5f;
	else if (colorFactor < 4.f) colorK = 0.75;
	else colorK = 1.f;

	PColor color = PColor::Lerp(PColor::Green, PColor::Red, colorK);

	PDebugRenderer::GetInstance().DrawDebugLine(_anchor, particle->GetPosition(), 4.f, color);
}
// ----------------------------------------------------------------------------