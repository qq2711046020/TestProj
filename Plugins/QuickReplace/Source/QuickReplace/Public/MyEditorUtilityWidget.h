// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "MyEditorUtilityWidget.generated.h"

/**
 * 
 */
UCLASS()
class QUICKREPLACE_API UMyEditorUtilityWidget : public UEditorUtilityWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Editor")
	void UpdateAllTextFont(const FString& RootPath);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Editor")
	bool ProcessTextWidget(UTextBlock* Text);
};
