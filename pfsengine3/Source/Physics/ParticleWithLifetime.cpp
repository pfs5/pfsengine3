#include "ParticleWithLifetime.h"
// ----------------------------------------------------------------------------
OParticleWithLifetime::OParticleWithLifetime(const PVector2& position /*= PVector2::ZeroVector*/, const PVector2& velocity /*= PVector2::ZeroVector*/, float lifetime /*= -1.f*/):
	OParticle(position, velocity),
	_lifetime(lifetime),
	_lifeCounter(0.f)
{

}
// ----------------------------------------------------------------------------
/*override*/
void OParticleWithLifetime::Update(float deltaTime)
{
	OParticle::Update(deltaTime);

	if (_lifetime > 0.f)
	{
		_lifeCounter += deltaTime;
		if (_lifeCounter >= _lifetime)
		{
			Destroy();
		}
	}
}
// ----------------------------------------------------------------------------