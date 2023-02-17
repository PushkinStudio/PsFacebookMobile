// Copyright 2015-2023 MY.GAMES. All Rights Reserved.

#pragma once

#include "PsFacebookMobileSettings.generated.h"

UCLASS(config = Engine, defaultconfig)
class PSFACEBOOKMOBILE_API UPsFacebookMobileSettings : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	/** Plugin enabled flag */
	UPROPERTY(Config, EditAnywhere, Category = "Pushkin Facebook Mobile Settings")
	bool bEnableFacebook;

	/** Facebook App ID */
	UPROPERTY(Config, EditAnywhere, Category = "Pushkin Facebook Mobile Settings")
	FString FacebookAppId;

	/** Facebook display name */
	UPROPERTY(Config, EditAnywhere, Category = "Pushkin Facebook Mobile Settings")
	FString FacebookDisplayName;

	/** Facebook client token */
	UPROPERTY(Config, EditAnywhere, Category = "Pushkin Facebook Mobile Settings")
	FString FacebookClientToken;
};
