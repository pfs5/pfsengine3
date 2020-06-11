#include "Input/InputManager.h"
#include "Math/Vector2.h"
#include "ParticleSystemLevel.h"
#include "Physics/ContactGenerators/CableParticleContactGenerator.h"
#include "Physics/ContactGenerators/RodParticleContactGenerator.h"
#include "Physics/ForceGenerators/FixedSpringParticleForceGenerator.h"
#include "Physics/ForceGenerators/SpringParticleForceGenerator.h"
#include "Physics/ParticleWithLifetime.h"
#include "Physics/PhysicsSystem.h"
#include "Rendering/PFSEngineWindow.h"
// ----------------------------------------------------------------------------
PParticleSystemLevel::PParticleSystemLevel()
{
	
}
// ----------------------------------------------------------------------------
/*override*/
void PParticleSystemLevel::Draw(PRenderTarget* renderTarget)
{
	PLevel::Draw(renderTarget);
}
// ----------------------------------------------------------------------------
/*override*/
void PParticleSystemLevel::Update(float deltaTime)
{
	PLevel::Update(deltaTime);

	static OParticle* _lastParticle = nullptr;
	static OParticle* _firstParticle = nullptr;
	static bool _followMouse = false;

	if (_followMouse && _firstParticle != nullptr)
	{
		PVector2 mousePosition = PInput::GetMousePosition(PWindow::MainWindow);
		_firstParticle->SetPosition(mousePosition);
	}

	// Follow mouse toggle
	if (PInput::GetKeyDown(PInput::SPACE))
	{
		_followMouse = !_followMouse;
	}

	// Click
	if (PInput::GetKeyDown(PInput::MOUSE_RIGHT))
	{
		PVector2 mousePosition = PInput::GetMousePosition(PWindow::MainWindow);
		if (PWindow::MainWindow->IsPointInWindow(mousePosition))
		{
			OParticle* testParticle = new OParticleWithLifetime(mousePosition, PVector2(0.f, 0.f));
			testParticle->SetName("Particle");
			testParticle->UseGravity(true);
			testParticle->SetMass(10.f);
			testParticle->SetDragCoeff(.9f);

			if (_lastParticle == nullptr)
			{
				// first particle
				testParticle->UseGravity(false);
				testParticle->SetInverseMass(0.f);
				_firstParticle = testParticle;

				//PFixedSpringParticleForceGenerator* springForceGen = new PFixedSpringParticleForceGenerator(mousePosition, 40.f, 40.f);
				//PPhysicsSystem::GetInstance().AddForceGenerator(springForceGen, testParticle);
			}
			else
			{
				//PSpringParticleForceGenerator* springForceGen = new PSpringParticleForceGenerator(_lastParticle, 100.f, 40.f);
				//PPhysicsSystem::GetInstance().AddForceGenerator(springForceGen, testParticle);

				PCableParticleContactGenerator* cableContactGen = new PCableParticleContactGenerator(_lastParticle, testParticle, 150.f, 0.f);
				PRodParticleContactGenerator* rodContactGen = new PRodParticleContactGenerator(_lastParticle, testParticle, 150.f);
				PPhysicsSystem::GetInstance().AddContactGenerator(rodContactGen);
			}

			AttachObjectToRoot(testParticle);

			_lastParticle = testParticle;
		}
	}
}
// ----------------------------------------------------------------------------