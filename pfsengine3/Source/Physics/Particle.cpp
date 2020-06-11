#include "Container/PFSEngineColor.h"
#include "Particle.h"
#include "PhysicsGlobals.h"
#include "Rendering/RenderTarget.h"
// ----------------------------------------------------------------------------
OParticle::OParticle(const PVector2& position /*= PVector2::ZeroVector*/, const PVector2& velocity /*= PVector2::ZeroVector*/):
	_position(position),
	_velocity(velocity)
{
	_shape.setFillColor(PColor::White);
	_shape.setRadius(7.f);
	_shape.setOrigin(PVector2::OneVector * _shape.getRadius());
}
// ----------------------------------------------------------------------------
void OParticle::UseGravity(bool value)
{
	_useGravity = value;
}
// ----------------------------------------------------------------------------
void OParticle::SetMass(float value)
{
	_mass = value;
	_inverseMass = 1.f / value;
}
// ----------------------------------------------------------------------------
float OParticle::GetMass() const
{
	return _mass;
}
// ----------------------------------------------------------------------------
void OParticle::SetInverseMass(float value)
{
	_mass = 1.f / value;
	_inverseMass = value;
}
// ----------------------------------------------------------------------------
float OParticle::GetInverseMass() const
{
	return _inverseMass;
}
// ----------------------------------------------------------------------------
void OParticle::SetDragCoeff(float value)
{
	_dragCoefficient = value;
}
// ----------------------------------------------------------------------------
void OParticle::SetAcceleration(const PVector2& value)
{
	_acceleration = value;
}
// ----------------------------------------------------------------------------
const PVector2& OParticle::GetAcceleration() const
{
	return _acceleration;
}
// ----------------------------------------------------------------------------
void OParticle::SetVelocity(const PVector2& value)
{
	_velocity = value;
}
// ----------------------------------------------------------------------------
const PVector2& OParticle::GetVelocity() const
{
	return _velocity;
}
// ----------------------------------------------------------------------------
void OParticle::SetPosition(const PVector2& value)
{
	_position = value;
}
// ----------------------------------------------------------------------------
const PVector2& OParticle::GetPosition() const
{
	return _position;
}
// ----------------------------------------------------------------------------
void OParticle::AddForce(const PVector2& force)
{
	_accumulatedForce += force;
}
// ----------------------------------------------------------------------------
void OParticle::Draw(PRenderTarget* renderTarget)
{
	OWorldObject::Draw(renderTarget);

	_shape.setPosition(_position);
	renderTarget->Draw(_shape);
}
// ----------------------------------------------------------------------------
void OParticle::Update(float deltaTime)
{
	OWorldObject::Update(deltaTime);

	Integrate(deltaTime);
}
// ----------------------------------------------------------------------------
void OParticle::Integrate(float deltaTime)
{
	_acceleration = _accumulatedForce * _inverseMass;
	_acceleration += _useGravity ? PVector2(0.f, PPhysicsGlobals::GRAVITY) : PVector2::ZeroVector;

	_position += _velocity * deltaTime;

	_velocity *= PPhysicsGlobals::GetVelocityDampingFactor();
	_velocity *= !PMath::IsNearlyEqual(_dragCoefficient, 1.f) ? PMath::Pow(_dragCoefficient, deltaTime) : 1.f;
	_velocity += _acceleration * deltaTime;

	ClearForces();
}
// ----------------------------------------------------------------------------
void OParticle::ClearForces()
{
	_accumulatedForce = PVector2::ZeroVector;
}
// ----------------------------------------------------------------------------