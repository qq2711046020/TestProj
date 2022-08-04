// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/HorizontalBox.h"
#include "HorizontalBoxEx.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnIsMirrorChangedDynamic, bool, bIsMirror);
/**
 * 
 */
UCLASS()
class TESTPROJ_API UHorizontalBoxEx : public UHorizontalBox
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "HorizontalBoxEx")
	void SetIsMirror(bool bIsMirror);

	/** The amount of padding between the slots parent and the content. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Content")
	FMargin Padding;

	/** How much space this slot should occupy in the direction of the panel. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Content")
	FSlateChildSize Size;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Content")
	TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Content")
	TEnumAsByte<EVerticalAlignment> VerticalAlignment;

	UFUNCTION(BlueprintCallable, Category = "Widget")
	UHorizontalBoxSlot* AddChildToHorizontalBoxEx(UWidget* Content);

protected:
	UPROPERTY(BlueprintAssignable, Category = Events, meta = (DisplayName = "On Is Mirror Changed"))
	FOnIsMirrorChangedDynamic BP_IsMirrorChanged;

	virtual void OnSlotAdded(UPanelSlot* Slot) override;
	virtual void OnSlotRemoved(UPanelSlot* Slot) override;
};
