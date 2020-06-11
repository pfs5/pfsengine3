#pragma once
#include "Math/Vector2.h"
// ----------------------------------------------------------------------------
class OParticle;
// ----------------------------------------------------------------------------
struct PPhysicsParticleContact
{
	OParticle* Particles[2];
	float Restitution;
	PVector2 ContactNormal;
	float Penetration;
};
// ----------------------------------------------------------------------------