// Copyright Epic Games, Inc. All Rights Reserved.

#include "HorizontalBoxEx.h"
#include "Components/HorizontalBoxSlot.h"

#define LOCTEXT_NAMESPACE "UMG"

/////////////////////////////////////////////////////
// UHorizontalBoxEx

UHorizontalBoxEx::UHorizontalBoxEx(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bIsVariable = false;
	Visibility = ESlateVisibility::SelfHitTestInvisible;
}

void UHorizontalBoxEx::SetIsMirror(bool bIsMirror)
{
	TSharedPtr<SWidget> SafeWidget = GetCachedWidget();
	if (!SafeWidget.IsValid())
	{
		return;
	}
	if (bIsMirror)
	{
		SafeWidget->SetFlowDirectionPreference(EFlowDirectionPreference::RightToLeft);
	}
	else
	{
		SafeWidget->SetFlowDirectionPreference(EFlowDirectionPreference::LeftToRight);
	}
	BP_IsMirrorChanged.Broadcast(bIsMirror);
}

void UHorizontalBoxEx::UpdateChildSlot(UHorizontalBoxSlot* ChildSlot)
{
	ChildSlot->SetPadding(Padding);
	ChildSlot->SetSize(Size);
	ChildSlot->SetHorizontalAlignment(HorizontalAlignment);
	ChildSlot->SetVerticalAlignment(VerticalAlignment);
}

void UHorizontalBoxEx::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	MyHorizontalBox.Reset();
}

UClass* UHorizontalBoxEx::GetSlotClass() const
{
	return UHorizontalBoxSlot::StaticClass();
}

void UHorizontalBoxEx::OnSlotAdded(UPanelSlot* InSlot)
{
	// Add the child to the live canvas if it already exists
	if (MyHorizontalBox.IsValid())
	{
		if (UHorizontalBoxSlot* ChildSlot = CastChecked<UHorizontalBoxSlot>(InSlot))
		{
			ChildSlot->BuildSlot(MyHorizontalBox.ToSharedRef());
			UpdateChildSlot(ChildSlot);
		}
	}
}

void UHorizontalBoxEx::OnSlotRemoved(UPanelSlot* InSlot)
{
	// Remove the widget from the live slot if it exists.
	if (MyHorizontalBox.IsValid() && InSlot->Content)
	{
		TSharedPtr<SWidget> Widget = InSlot->Content->GetCachedWidget();
		if (Widget.IsValid())
		{
			MyHorizontalBox->RemoveSlot(Widget.ToSharedRef());
		}
	}
}

UHorizontalBoxSlot* UHorizontalBoxEx::AddChildToHorizontalBox(UWidget* Content)
{
	UHorizontalBoxSlot* ChildSlot = Cast<UHorizontalBoxSlot>(Super::AddChild(Content));
	UpdateChildSlot(ChildSlot);
	return ChildSlot;
}

TSharedRef<SWidget> UHorizontalBoxEx::RebuildWidget()
{
	MyHorizontalBox = SNew(SHorizontalBox);

	for (UPanelSlot* PanelSlot : Slots)
	{
		if (UHorizontalBoxSlot* TypedSlot = Cast<UHorizontalBoxSlot>(PanelSlot))
		{
			TypedSlot->Parent = this;
			TypedSlot->BuildSlot(MyHorizontalBox.ToSharedRef());
			UpdateChildSlot(TypedSlot);
		}
	}

	return MyHorizontalBox.ToSharedRef();
}

#if WITH_EDITOR

const FText UHorizontalBoxEx::GetPaletteCategory()
{
	return LOCTEXT("Panel", "Panel");
}

#endif

/////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE
