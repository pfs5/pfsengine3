#include "Level.h"
#include "WorldObject/Nameable.h"
#include "WorldObject/WorldObject.h"
#include "WorldObject/WorldObjectManager.h"
// ----------------------------------------------------------------------------
PLevel::PLevel()
{
	_rootWorldObject = new OWorldObject("RootObject");
}
// ----------------------------------------------------------------------------
PLevel::~PLevel()
{
	PWorldObjectManager::GetInstance().DestroyWorldObject(_rootWorldObject);
}
// ----------------------------------------------------------------------------
void PLevel::AttachObjectToRoot(OWorldObject* obj)
{
	if (_rootWorldObject == nullptr)
	{
		return;
	}

	obj->AttachTo(_rootWorldObject);
}
// ----------------------------------------------------------------------------
OWorldObject* PLevel::GetRootObject() const
{
	return _rootWorldObject;
}
// ----------------------------------------------------------------------------
void PLevel::Draw(PRenderTarget* renderTarget)
{
	DrawInternal(renderTarget, _rootWorldObject);
}
// ----------------------------------------------------------------------------
void PLevel::Update(float deltaTime)
{
	UpdateInternal(deltaTime, _rootWorldObject);
}
// ----------------------------------------------------------------------------
PString PLevel::DumpContent() const
{
	// Dump objects tree
	PString treeDump;
	DumpTreeLevel(treeDump, _rootWorldObject);
	return treeDump;
}
// ----------------------------------------------------------------------------
void PLevel::DumpTreeLevel(PString& outDump, const ITransformable* root, int level /*= 0*/) const
{
	if (root == nullptr)
	{
		return;
	}

	for (int i = 0; i < level; ++i)
	{
		outDump += "...";
	}

	if (const INameable* nameable = dynamic_cast<const INameable*>(root))
	{
		outDump += nameable->GetName();
	}

	outDump += "\n";

	for (const ITransformable* child : root->GetChildren())
	{
		DumpTreeLevel(outDump, child, level + 1);
	}
}
// ----------------------------------------------------------------------------
void PLevel::DrawInternal(PRenderTarget* renderTarget, OWorldObject* root)
{
	root->Draw(renderTarget);

	for (OWorldObject* child : root->GetChildren())
	{
		DrawInternal(renderTarget, child);
	}
}
// ----------------------------------------------------------------------------
void PLevel::UpdateInternal(float deltaTime, OWorldObject* root)
{
	root->Update(deltaTime);

	for (OWorldObject* child : root->GetChildren())
	{
		UpdateInternal(deltaTime, child);
	}
}
// ----------------------------------------------------------------------------