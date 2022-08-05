// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Widgets/SWidget.h"
#include "Widgets/SBoxPanel.h"
#include "Components/PanelWidget.h"
#include "HorizontalBoxEx.generated.h"

class UHorizontalBoxExSlot;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnIsMirrorChangedDynamic, bool, bIsMirror);
/**
 * Allows widgets to be laid out in a flow horizontally.
 *
 * * Many Children
 * * Flow Horizontal
 */
UCLASS(meta = (ShortTooltip = "A layout panel for automatically laying child widgets out horizontally"))
class TESTPROJ_API UHorizontalBoxEx : public UPanelWidget
{
	GENERATED_UCLASS_BODY()

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

	/**  */
	UFUNCTION(BlueprintCallable, Category = "Widget")
	UHorizontalBoxExSlot* AddChildToHorizontalBox(UWidget* Content);

#if WITH_EDITOR
	// UWidget interface
	virtual const FText GetPaletteCategory() override;
	// End UWidget interface
#endif

	void UpdateChildSlot(UHorizontalBoxExSlot* ChildSlot);

	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

protected:
	UPROPERTY(BlueprintAssignable, Category = Events, meta = (DisplayName = "On Is Mirror Changed"))
	FOnIsMirrorChangedDynamic BP_IsMirrorChanged;

	// UPanelWidget
	virtual UClass* GetSlotClass() const override;
	virtual void OnSlotAdded(UPanelSlot* Slot) override;
	virtual void OnSlotRemoved(UPanelSlot* Slot) override;
	// End UPanelWidget

protected:

	TSharedPtr<class SHorizontalBox> MyHorizontalBox;

protected:
	// UWidget interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
	// End of UWidget interface
};
