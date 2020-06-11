#pragma once
#include "Math/Vector2.h"
#include "Particle.h"
// ----------------------------------------------------------------------------
class OParticleWithLifetime : public OParticle
{
public:
	OParticleWithLifetime(const PVector2& position = PVector2::ZeroVector, const PVector2& velocity = PVector2::ZeroVector, float lifetime = -1.f);

// OParticle
public:
	virtual void Update(float deltaTime) override;

private:
	float _lifetime;
	float _lifeCounter;
};
// ----------------------------------------------------------------------------