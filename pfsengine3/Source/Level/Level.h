#pragma once
#include "Misc/PFSEngineString.h"
// ----------------------------------------------------------------------------
class ITransformable;
class OWorldObject;
class PRenderTarget;
// ----------------------------------------------------------------------------
class PLevel
{
public:
	PLevel();
	~PLevel();

	void AttachObjectToRoot(OWorldObject* obj);
	OWorldObject* GetRootObject() const;

	virtual void Draw(PRenderTarget* renderTarget);
	virtual void Update(float deltaTime);

	PString DumpContent() const;
	void DumpTreeLevel(PString& outDump, const ITransformable* root, int level = 0) const;

private:
	OWorldObject* _rootWorldObject;

private:
	void DrawInternal(PRenderTarget* renderTarget, OWorldObject* root);
	void UpdateInternal(float deltaTime, OWorldObject* root);
};
// ----------------------------------------------------------------------------