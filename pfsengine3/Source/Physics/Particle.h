#pragma once
#include "Math/Vector2.h"
#include "SFML/Graphics/CircleShape.hpp"
#include "WorldObject/WorldObject.h"
// ----------------------------------------------------------------------------
class OParticle : public OWorldObject
{
public:
	OParticle(const PVector2& position = PVector2::ZeroVector, const PVector2& velocity = PVector2::ZeroVector);

	void UseGravity(bool value);

	void SetMass(float value);
	float GetMass() const;

	void SetInverseMass(float value);
	float GetInverseMass() const;

	void SetDragCoeff(float value);

	void SetAcceleration(const PVector2& value);
	const PVector2& GetAcceleration() const;

	void SetVelocity(const PVector2& value);
	const PVector2& GetVelocity() const;

	void SetPosition(const PVector2& value);
	const PVector2& GetPosition() const;

	void AddForce(const PVector2& force);

// OWorldObject
public:
	virtual void Draw(PRenderTarget* renderTarget) override;
	virtual void Update(float deltaTime) override;

private:
	PVector2 _position;
	PVector2 _velocity;
	PVector2 _acceleration;
	PVector2 _accumulatedForce;

	bool _useGravity = false;

	float _mass = 1.f;
	float _inverseMass = 1.f;

	float _dragCoefficient = 1.f;

	sf::CircleShape _shape;

private:
	void Integrate(float deltaTime);
	void ClearForces();
};
// ----------------------------------------------------------------------------