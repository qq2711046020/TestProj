// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ListView.h"
#include "ListViewEx.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnListViewScrolledDynamic, float, ItemOffset, float, DistanceRemaining);

/**
 * 
 */
UCLASS()
class TESTPROJ_API UListViewEx : public UListView
{
	GENERATED_UCLASS_BODY()
public:
	DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(TSubclassOf<UUserWidget>, FOnGetEntryWidgetClass, UObject*, Item);

	UPROPERTY(EditAnywhere, Category = "Events")
		FOnGetEntryWidgetClass OnGetEntryWidgetEvent;
	
protected:
	virtual void OnListViewScrolledInternal(float ItemOffset, float DistanceRemaining) override;
	virtual UUserWidget& OnGenerateEntryWidgetInternal(UObject* Item, TSubclassOf<UUserWidget> DesiredEntryClass, const TSharedRef<STableViewBase>& OwnerTable) override;

private:
	UPROPERTY(BlueprintAssignable, Category = Events, meta = (DisplayName = "On ListView Scrolled"))
		FOnListViewScrolledDynamic BP_OnListViewScrolled;
};
