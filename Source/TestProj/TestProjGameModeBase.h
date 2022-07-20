// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TestProjGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJ_API ATestProjGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual bool ProcessConsoleExec(const TCHAR* Cmd, FOutputDevice& Ar, UObject* Executor) override;
};
