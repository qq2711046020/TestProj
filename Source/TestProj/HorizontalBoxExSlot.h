// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Layout/Margin.h"
#include "Widgets/SBoxPanel.h"
#include "Components/PanelSlot.h"
#include "Components/SlateWrapperTypes.h"

#include "HorizontalBoxExSlot.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJ_API UHorizontalBoxExSlot : public UPanelSlot
{
	GENERATED_UCLASS_BODY()

private:
	SHorizontalBox::FSlot* Slot;

public:
	/** 是否自定义布局 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Layout|Horizontal Box Ex Slot")
	bool bIsCustomLayout;

	/** 由HorizontalBoxEx传来的预设值 */
	FMargin Raw_Padding;

	FSlateChildSize Raw_Size;

	TEnumAsByte<EHorizontalAlignment> Raw_HorizontalAlignment;

	TEnumAsByte<EVerticalAlignment> Raw_VerticalAlignment;
	
	/** The amount of padding between the slots parent and the content. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Layout|Horizontal Box Ex Slot")
	FMargin Padding;

	/** How much space this slot should occupy in the direction of the panel. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Layout|Horizontal Box Ex Slot")
	FSlateChildSize Size;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Layout|Horizontal Box Ex Slot")
	TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Layout|Horizontal Box Ex Slot")
	TEnumAsByte<EVerticalAlignment> VerticalAlignment;

	UFUNCTION(BlueprintCallable, Category = "Layout|Horizontal Box Ex Slot")
	void SetPadding(FMargin InPadding);

	UFUNCTION(BlueprintCallable, Category = "Layout|Horizontal Box Ex Slot")
	void SetSize(FSlateChildSize InSize);

	UFUNCTION(BlueprintCallable, Category = "Layout|Horizontal Box Ex Slot")
	void SetHorizontalAlignment(EHorizontalAlignment InHorizontalAlignment);

	UFUNCTION(BlueprintCallable, Category = "Layout|Horizontal Box Ex Slot")
	void SetVerticalAlignment(EVerticalAlignment InVerticalAlignment);

	UFUNCTION(BlueprintCallable, Category = "Layout|Horizontal Box Ex Slot")
	void UpdateSlotPadding();

	UFUNCTION(BlueprintCallable, Category = "Layout|Horizontal Box Ex Slot")
	void UpdateSlotSize();

	UFUNCTION(BlueprintCallable, Category = "Layout|Horizontal Box Ex Slot")
	void UpdateSlotHorizontalAlignment();

	UFUNCTION(BlueprintCallable, Category = "Layout|Horizontal Box Ex Slot")
	void UpdateSlotVerticalAlignment();

	void BuildSlot(TSharedRef<SHorizontalBox> HorizontalBox);

	// UPanelSlot interface
	virtual void SynchronizeProperties() override;
	// End of UPanelSlot interface

	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
};
