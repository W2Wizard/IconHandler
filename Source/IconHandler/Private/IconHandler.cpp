// Copyright (c) W2.Wizard 2020-2021. All Rights Reserved.

#include "IconHandler.h"

#define LOCTEXT_NAMESPACE "FIconHandlerModule"
DEFINE_LOG_CATEGORY(LogIconHandler);

void FIconHandlerModule::StartupModule()
{
	// Register module & settings
	ModuleSettings = NewObject<UIconHandlerSettings>(GetTransientPackage(), "IconHandlerSettings", RF_Standalone);
	ModuleSettings->AddToRoot();

	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings(
			"Project",
			"Editor",
			"ProjectIcons",
			LOCTEXT("RuntimeSettingsName", "Project Icons"),
			LOCTEXT("RuntimeSettingsDescription", "Configure IconHandler plugin settings"),
			ModuleSettings);
	}

	// Apply icons
	if (ModuleSettings->Enable && ModuleSettings->Icons.Num() != 0)
	{
		StyleWasImplemented = true;
		
		FName Property;
		UTexture2D* Texture;
		
		const FVector2D Icon64(64.f, 64.f);
		const FVector2D Icon16(16.0f, 16.0f);

		Style = MakeShareable(new FSlateStyleSet("IconHandlerStyle"));

		UE_LOG(LogIconHandler, Log, TEXT("Loading icons ..."));
		for (auto Entry : ModuleSettings->Icons)
		{
			if (!Entry.Key) continue;
			
			UE_LOG(LogIconHandler, Log, TEXT("Processing class %s..."), *Entry.Key->GetName());
			
			// Thumbnail
			if (Entry.Value.IsThumbnailValid())
			{
				if ((Texture = LoadObject<UTexture2D>(nullptr, *Entry.Value.ClassThumbnail.ToString())))
				{
					Property = FName(FString::Format(TEXT("ClassThumbnail.{0}"), { Entry.Key->GetName() }));
					Style->Set(Property, new FSlateImageBrush(Texture, Icon64));		
				}
			}

			// Icon
			if (Entry.Value.isIconValid())
			{
				if ((Texture = LoadObject<UTexture2D>(nullptr, *Entry.Value.ClassIcon.ToString())))
				{
					Property = FName(FString::Format(TEXT("ClassIcon.{0}"), { Entry.Key->GetName() }));
					Style->Set(Property, new FSlateImageBrush(Texture, Icon16));		
				}
			}
		}
		
		FSlateStyleRegistry::RegisterSlateStyle(*Style);
		UE_LOG(LogIconHandler, Log, TEXT("Finished loading icons"));
	}
	
}

void FIconHandlerModule::ShutdownModule()
{
	if (StyleWasImplemented)
		FSlateStyleRegistry::UnRegisterSlateStyle(Style->GetStyleSetName());

	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
		SettingsModule->UnregisterSettings("Project", "Plugins", "IconHandler");
	
	if (!GExitPurge)
		ModuleSettings->RemoveFromRoot();
	else
		ModuleSettings = nullptr;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FIconHandlerModule, IconHandler)