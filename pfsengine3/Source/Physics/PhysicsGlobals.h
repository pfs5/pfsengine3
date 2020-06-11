#pragma once
// ----------------------------------------------------------------------------
class PPhysicsGlobals
{
public:
	static const float GRAVITY;

public:
	static void UpdateVelocityDampingFactor(float deltaTime);
	static float GetVelocityDampingFactor();

private:
	static const float VELOCITY_DAMPING_FACTOR;

private:
	static float _currentVelocityDampingFactor;
};
// ----------------------------------------------------------------------------