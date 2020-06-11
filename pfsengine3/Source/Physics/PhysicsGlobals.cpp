#include "Math/Math.h"
#include "PhysicsGlobals.h"
// ----------------------------------------------------------------------------
const float PPhysicsGlobals::GRAVITY = 981.f;
const float PPhysicsGlobals::VELOCITY_DAMPING_FACTOR = 0.9f;
// ----------------------------------------------------------------------------
float PPhysicsGlobals::_currentVelocityDampingFactor = 1.f;
// ----------------------------------------------------------------------------
/*static*/
void PPhysicsGlobals::UpdateVelocityDampingFactor(float deltaTime)
{
	_currentVelocityDampingFactor = PMath::Pow(VELOCITY_DAMPING_FACTOR, deltaTime);
}
// ----------------------------------------------------------------------------
/*static*/
float PPhysicsGlobals::GetVelocityDampingFactor()
{
	return _currentVelocityDampingFactor;
}
// ----------------------------------------------------------------------------