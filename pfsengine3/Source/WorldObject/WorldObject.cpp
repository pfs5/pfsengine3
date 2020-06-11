#include "Logging/DebugLog.h"
#include "Rendering/RenderTarget.h"
#include "WorldObject.h"
#include "WorldObjectManager.h"
// ----------------------------------------------------------------------------
OWorldObject::OWorldObject(const PString& name /*= PString()*/):
	_name(name)
{
	PWorldObjectManager::GetInstance().OnWorldObjectCreated(this);
}
// ----------------------------------------------------------------------------
void OWorldObject::SetName(const PString& name)
{
	_name = name;
}
// ----------------------------------------------------------------------------
PString OWorldObject::GetName() const
{
	return _name;
}
// ----------------------------------------------------------------------------
const PArray<OWorldObject*> OWorldObject::GetChildren() const
{
	static PArray<OWorldObject*> children;
	children.Clear(ITransformable::GetChildren().Size());

	for (ITransformable* child : ITransformable::GetChildren())
	{
		if (OWorldObject* childObject = dynamic_cast<OWorldObject*>(child))
		{
			children.Add(childObject);
		}
	}
	return children;
}
// ----------------------------------------------------------------------------
OWorldObject* OWorldObject::GetParent() const
{
	return dynamic_cast<OWorldObject*>(ITransformable::GetParent());
}
// ----------------------------------------------------------------------------
void OWorldObject::Destroy()
{
	PWorldObjectManager::GetInstance().DestroyWorldObject(this);
}
// ----------------------------------------------------------------------------
void OWorldObject::Draw(PRenderTarget* renderTarget)
{

}
// ----------------------------------------------------------------------------
void OWorldObject::Update(float deltaTime)
{

}
// ----------------------------------------------------------------------------
/*virtual*/
OWorldObject::~OWorldObject()
{
	ITransformable* parent = GetParent();
	for (OWorldObject* child : GetChildren())
	{
		if (parent == nullptr)
		{
			child->DettachFromParent();
		}
		else
		{
			child->AttachTo(parent);
		}
	}

	DettachFromParent();
}
// ----------------------------------------------------------------------------
void OWorldObject::OnParentChanged()
{
	PWorldObjectManager::GetInstance().OnWorldObjectParentChanged(this);
}
// ----------------------------------------------------------------------------