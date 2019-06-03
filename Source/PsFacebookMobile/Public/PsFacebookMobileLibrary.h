// Copyright 2015-2019 Mail.Ru Group. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "PsFacebookMobileLibrary.generated.h"

UCLASS()
class PSFACEBOOKMOBILE_API UPsFacebookMobileLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:
	/** */
	UFUNCTION(BlueprintCallable, Category = "Pushkin Facebook Mobile")
	static void FacebookLogin(const FString& LoginPermissions);
};
