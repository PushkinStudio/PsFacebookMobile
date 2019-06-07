// Copyright 2015-2019 Mail.Ru Group. All Rights Reserved.

#pragma once

#include "PsFacebookMobileSettings.generated.h"

UCLASS(config = Engine, defaultconfig)
class PSFACEBOOKMOBILE_API UPsFacebookMobileSettings : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	/** */
	UPROPERTY(Config, EditAnywhere, Category = "Pushkin Facebook Mobile Settings")
	bool bEnableFacebook;

	/** */
	UPROPERTY(Config, EditAnywhere, Category = "Pushkin Facebook Mobile Settings")
	FString FacebookAppId;

	/** */
	UPROPERTY(Config, EditAnywhere, Category = "Pushkin Facebook Mobile Settings")
	FString FacebookDisplayName;
};
