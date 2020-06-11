#pragma once
#include "Math/Vector2.h"
#include "ParticleForceGenerator.h"
// ----------------------------------------------------------------------------
class PFixedSpringParticleForceGenerator : public PParticleForceGenerator
{
public:
	PFixedSpringParticleForceGenerator(const PVector2& anchor, float springConstant, float restLength);

	void SetAnchor(const PVector2& anchor);

// PParticleForceGenerator
public:
	virtual void UpdateForce(OParticle* particle, float deltaTime) override;

private:
	PVector2 _anchor;
	float _springConstant;
	float _restLength;
};
// ----------------------------------------------------------------------------