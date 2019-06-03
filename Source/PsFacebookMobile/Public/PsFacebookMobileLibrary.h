// Copyright 2015-2019 Mail.Ru Group. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "PsFacebookMobileLibrary.generated.h"

UCLASS()
class PSFACEBOOKMOBILE_API UPsFacebookMobileLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:
	/** Global PsFacebookMobileProxy accessor */
	UFUNCTION(BlueprintPure, Category = PsFacebookMobile, meta = (DisplayName = "Get PsFacebookMobile Proxy"))
	static UPsFacebookMobileProxy* GetPsFacebookMobileProxy();
};
