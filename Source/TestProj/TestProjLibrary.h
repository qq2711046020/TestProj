// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TestProjLibrary.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJ_API UTestProjLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Config")
	static FString GetConfig(const FString& Section, const FString& Key, const FString& Path);

	UFUNCTION(BlueprintCallable, Category = "Config")
	static void SetConfig(const FString& Section, const FString& Key, const FString& Value, const FString& Path);
};
