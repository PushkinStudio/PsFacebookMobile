// Copyright 2015-2019 Mail.Ru Group. All Rights Reserved.

#pragma once

#include "PsFacebookMobileSettings.generated.h"

UCLASS(config = Engine, defaultconfig)
class PSFACEBOOKMOBILE_API UPsFacebookMobileSettings : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	/** */
	UPROPERTY(Config, EditAnywhere)
	bool bEnableFacebook;

	/** */
	UPROPERTY(Config, EditAnywhere)
	FString FacebookAppId;
};
