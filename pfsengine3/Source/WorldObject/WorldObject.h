#pragma once
#include "Misc/PFSEngineString.h"
#include "Nameable.h"
#include "Transformable.h"
// ----------------------------------------------------------------------------
class OWorldObject : public ITransformable, public INameable
{
public:
	OWorldObject(const PString& name = PString());

	virtual void SetName(const PString& name) override;
	virtual PString GetName() const  override;

	const PArray<OWorldObject*> GetChildren() const;

private:
	PString _name;
};
// ----------------------------------------------------------------------------