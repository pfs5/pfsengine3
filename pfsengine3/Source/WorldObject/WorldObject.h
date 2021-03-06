#pragma once
#include "Misc/PFSEngineString.h"
#include "Nameable.h"
#include "Transformable.h"
// ----------------------------------------------------------------------------
class PRenderTarget;
class PWorldObjectManager;
// ----------------------------------------------------------------------------
class OWorldObject : public ITransformable, public INameable
{
public:
	OWorldObject(const PString& name = PString());

	virtual void SetName(const PString& name) override;
	virtual PString GetName() const  override;

	const PArray<OWorldObject*> GetChildren() const;
	OWorldObject* GetParent() const;

	void Destroy();

// To be overriden
public:
	virtual void Draw(PRenderTarget* renderTarget);
	virtual void Update(float deltaTime);

protected:
	virtual ~OWorldObject();

private:
	friend class PWorldObjectManager;

private:
	PString _name;

// ITransformable
protected:
	virtual void OnParentChanged() override;

};
// ----------------------------------------------------------------------------