// By Jason Hoku Levien, Published 2024


#pragma once

#include "Modules/ModuleManager.h"

class FHAETModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
