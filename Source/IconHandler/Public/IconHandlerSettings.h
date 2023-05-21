// Copyright (c) W2.Wizard 2020-2021. All Rights Reserved.

#pragma once

// Includes
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

// generated.h
#include "IconHandlerSettings.generated.h"

/** Entry used to configure the icons for a single class. */
USTRUCT()
struct FClassIconEntry
{
	GENERATED_BODY()

public: // Properties
	
	/** Icon used to display in the windows like the content browser. (64x64)*/
	UPROPERTY(EditAnywhere, meta=(AllowedClasses="/Script/Engine.Texture2D"))
	FSoftObjectPath ClassThumbnail;

	/** Icon used to display in tabs and/or anything small. (16x16) */
	UPROPERTY(EditAnywhere, meta=(AllowedClasses="/Script/Engine.Texture2D"))
	FSoftObjectPath ClassIcon;

public: // Methods

	/** Returns the relative reference path of the thumbnail asset. */
	FString GetThumbnailPath() { return ClassThumbnail.ToString(); }

	/** Returns the relative reference path of the icon asset. */
	FString GetIconPath() { return ClassIcon.ToString(); }

	/** Returns the thumbnail asset is valid. */
	bool IsThumbnailValid() { return ClassThumbnail.IsValid(); }

	/** Returns the icon asset is valid. */
	bool isIconValid() { return ClassIcon.IsValid(); }
};

/** Settings used to configure the Icon handler plugin itself. */
UCLASS(Config = Editor, Defaultconfig)
class ICONHANDLER_API UIconHandlerSettings final : public UObject
{
	GENERATED_BODY()

public: // Properties
	
	/** Master toggle wether to enable the icon changes or not. */
	UPROPERTY(EditAnywhere, Config, Category = "IconHandler", meta=(ConfigRestartRequired = true))
	bool Enable;
	
	/**
	 * Texture for this tutorial, used when presented to the user in the tutorial browser.
	 * @note Will only work with C++ created classes.
	 */
	UPROPERTY(EditAnywhere, Config, Category="IconHandler", meta=(ConfigRestartRequired = true))
	TMap<UClass*, FClassIconEntry> Icons;
	
};
