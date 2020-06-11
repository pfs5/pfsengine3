#pragma once
// ----------------------------------------------------------------------------
class OWorldObject;
// ----------------------------------------------------------------------------
class IWorldObjectEventListener
{
public:
	virtual void OnWorldObjectCreated(OWorldObject* worldObject) = 0;
	virtual void OnWorldObjectDestroyed(OWorldObject* worldObject) = 0;
	virtual void OnWorldObjectParentChanged(OWorldObject* worldObject) = 0;
};
// ----------------------------------------------------------------------------