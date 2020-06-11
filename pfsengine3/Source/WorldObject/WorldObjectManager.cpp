#include "ObjectListeners.h"
#include "WorldObject.h"
#include "WorldObjectManager.h"
// ----------------------------------------------------------------------------
PWorldObjectManager& PWorldObjectManager::GetInstance()
{
	static PWorldObjectManager Instance;
	return Instance;
}
// ----------------------------------------------------------------------------
void PWorldObjectManager::Update(float deltaTime)
{
	for (OWorldObject* worldObject : _objectDestroyQueue)
	{
		delete worldObject;
	}

	_objectDestroyQueue.Clear();
}
// ----------------------------------------------------------------------------
void PWorldObjectManager::DestroyWorldObject(OWorldObject* worldObject)
{
	_objectDestroyQueue.Add(worldObject);
	OnWorldObjectDestroyed(worldObject);
}
// ----------------------------------------------------------------------------
void PWorldObjectManager::OnWorldObjectCreated(OWorldObject* worldObject)
{
	for (IWorldObjectEventListener* listener : _creationListeners)
	{
		listener->OnWorldObjectCreated(worldObject);
	}
}
// ----------------------------------------------------------------------------
void PWorldObjectManager::OnWorldObjectDestroyed(OWorldObject* worldObject)
{
	for (IWorldObjectEventListener* listener : _creationListeners)
	{
		listener->OnWorldObjectDestroyed(worldObject);
	}
}
// ----------------------------------------------------------------------------
void PWorldObjectManager::OnWorldObjectParentChanged(OWorldObject* worldObject)
{
	for (IWorldObjectEventListener* listener : _creationListeners)
	{
		listener->OnWorldObjectParentChanged(worldObject);
	}
}
// ----------------------------------------------------------------------------
void PWorldObjectManager::RegisterWorldObjectCreationListener(IWorldObjectEventListener* listener)
{
	_creationListeners.Add(listener);
}
// ----------------------------------------------------------------------------
void PWorldObjectManager::UnregisterWorldObjectCreationListener(IWorldObjectEventListener* listener)
{
	_creationListeners.RemoveSwap(listener);
}
// ----------------------------------------------------------------------------