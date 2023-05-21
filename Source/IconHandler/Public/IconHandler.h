// Copyright (c) W2.Wizard 2020-2021. All Rights Reserved.

#pragma once

// Includes
#include "CoreMinimal.h"
#include "IconHandlerSettings.h"
#include "Modules/ModuleManager.h"
#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Developer/Settings/Public/ISettingsModule.h"

// Forward declarations
class UIconHandlerSettings;

// Macros
DECLARE_LOG_CATEGORY_EXTERN(LogIconHandler, Log, All);

/**  */
class FIconHandlerModule final : public IModuleInterface
{
	
public: // Fields

	/** The literal style itself. */
	TSharedPtr<FSlateStyleSet> Style;

public: // Methods
	
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/**
	* Singleton-like access to this module's interface. This is just for convenience!
	* Beware of calling this during the shutdown phase, though. Your module might have been unloaded already.
	*
	* @return Returns singleton instance, loading the module on demand if needed
	*/
	static FIconHandlerModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FIconHandlerModule>("IconHandler");
	}

	/**
	* Checks to see if this module is loaded and ready. It is only valid to call Get() if IsLoaded() returns true.
	*
	* @return True if the module is loaded and ready to use
	*/
	static bool IsLoaded()
	{
		return FModuleManager::Get().IsModuleLoaded("IconHandler");
	}

	/** Getter for internal settings object to support runtime configuration changes */
	UIconHandlerSettings* GetSettings() const
	{
		check(ModuleSettings);
		return ModuleSettings;
	}

protected: // Fields

	/** Indicates wether the style was implemented. */
	bool StyleWasImplemented = false;
	
	/** Module settings */
	UIconHandlerSettings* ModuleSettings = nullptr;
};
