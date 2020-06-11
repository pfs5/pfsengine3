#include "Container/PFSEngineColor.h"
#include "Rendering/RenderTarget.h"
#include "TestObject.h"
// ----------------------------------------------------------------------------
OTestObject::OTestObject(const PString& name/* = PString()*/):
	OWorldObject(name)
{
	_shape.setSize(PVector2(50.f, 50.f));
	_shape.setOrigin(_shape.getSize() / 2.f);
	_shape.setFillColor(PColor::Red);
}
// ----------------------------------------------------------------------------
void OTestObject::Draw(PRenderTarget* renderTarget)
{
	OWorldObject::Draw(renderTarget);

	_shape.setPosition(GetWorldLocation());

	renderTarget->Draw(_shape);
}
// ----------------------------------------------------------------------------
void OTestObject::Update(float deltaTime)
{
	OWorldObject::Update(deltaTime);
}
// ----------------------------------------------------------------------------