#pragma once
#include "Container/Array.h"
// ----------------------------------------------------------------------------
class IWorldObjectEventListener;
class OWorldObject;
// ----------------------------------------------------------------------------
class PWorldObjectManager
{
public:
	static PWorldObjectManager& GetInstance();

public:
	PWorldObjectManager() = default;

	void Update(float deltaTime);

	void DestroyWorldObject(OWorldObject* worldObject);

	void OnWorldObjectCreated(OWorldObject* worldObject);
	void OnWorldObjectDestroyed(OWorldObject* worldObject);
	void OnWorldObjectParentChanged(OWorldObject* worldObject);

	void RegisterWorldObjectCreationListener(IWorldObjectEventListener* listener);
	void UnregisterWorldObjectCreationListener(IWorldObjectEventListener* listener);

private:
	PArray<OWorldObject*> _objectDestroyQueue;
	PArray<IWorldObjectEventListener*> _creationListeners;
};
// ----------------------------------------------------------------------------
