#pragma once
#include "Misc/PFSEngineString.h"
// ----------------------------------------------------------------------------
class INameable
{
public:
	virtual void SetName(const PString& name) = 0;
	virtual PString GetName() const = 0;
};
// ----------------------------------------------------------------------------