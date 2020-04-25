#pragma once
#include "Transform.h"
#include <vector>
// ----------------------------------------------------------------------------
class ITransformable
{
public:
	const PTransform& GetTransform() const;
	void SetTransform(const PTransform& transform);

	void SetParent(ITransformable* parent);
	ITransformable* GetParent() const;

	std::vector<ITransformable*> GetChildren() const;
	void AddChild(ITransformable* child);
	void RemoveChild(ITransformable* child);
	void ClearChildren();

private:
	PTransform _transform;

	ITransformable* _parent = nullptr;
	std::vector<ITransformable*> _children;
};
// ----------------------------------------------------------------------------