#pragma once
#include "Level/Level.h"
// ----------------------------------------------------------------------------
class PParticleSystemLevel : public PLevel
{
public:
	PParticleSystemLevel();

// PLevel
public:
	virtual void Draw(PRenderTarget* renderTarget) override;
	virtual void Update(float deltaTime) override;
};
// ----------------------------------------------------------------------------