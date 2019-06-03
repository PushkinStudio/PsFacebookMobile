// Copyright 2015-2019 Mail.Ru Group. All Rights Reserved.

#include "PsFacebookMobileLibrary.h"

#include "PsFacebookMobile.h"

UPsFacebookMobileLibrary::UPsFacebookMobileLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UPsFacebookMobileProxy* UPsFacebookMobileLibrary::GetPsFacebookMobileProxy()
{
	return FPsFacebookMobileModule::Get().GetProxy();
}
