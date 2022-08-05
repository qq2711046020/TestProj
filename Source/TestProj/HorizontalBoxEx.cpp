// Copyright Epic Games, Inc. All Rights Reserved.

#include "HorizontalBoxEx.h"
#include "HorizontalBoxExSlot.h"

#define LOCTEXT_NAMESPACE "UMG"

/////////////////////////////////////////////////////
// UHorizontalBoxEx

UHorizontalBoxEx::UHorizontalBoxEx(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bIsVariable = false;
	Visibility = ESlateVisibility::SelfHitTestInvisible;
	HorizontalAlignment = HAlign_Fill;
	VerticalAlignment = VAlign_Fill;
	Size = FSlateChildSize(ESlateSizeRule::Automatic);
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

void UHorizontalBoxEx::UpdateChildSlot(UHorizontalBoxExSlot* ChildSlot)
{
	//ChildSlot->SetPadding(Padding);
	//ChildSlot->SetSize(Size);
	//ChildSlot->SetHorizontalAlignment(HorizontalAlignment);
	//ChildSlot->SetVerticalAlignment(VerticalAlignment);
	ChildSlot->Raw_Padding = Padding;
	ChildSlot->Raw_Size = Size;
	ChildSlot->Raw_HorizontalAlignment = HorizontalAlignment;
	ChildSlot->Raw_VerticalAlignment = VerticalAlignment;
	ChildSlot->SynchronizeProperties();
}

void UHorizontalBoxEx::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	MyHorizontalBox.Reset();
}

UClass* UHorizontalBoxEx::GetSlotClass() const
{
	return UHorizontalBoxExSlot::StaticClass();
}

void UHorizontalBoxEx::OnSlotAdded(UPanelSlot* InSlot)
{
	// Add the child to the live canvas if it already exists
	if (MyHorizontalBox.IsValid())
	{
		if (UHorizontalBoxExSlot* ChildSlot = CastChecked<UHorizontalBoxExSlot>(InSlot))
		{
			UpdateChildSlot(ChildSlot);
			ChildSlot->BuildSlot(MyHorizontalBox.ToSharedRef());
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

UHorizontalBoxExSlot* UHorizontalBoxEx::AddChildToHorizontalBox(UWidget* Content)
{
	UHorizontalBoxExSlot* ChildSlot = Cast<UHorizontalBoxExSlot>(Super::AddChild(Content));
	UpdateChildSlot(ChildSlot);
	return ChildSlot;
}

TSharedRef<SWidget> UHorizontalBoxEx::RebuildWidget()
{
	MyHorizontalBox = SNew(SHorizontalBox);

	for (UPanelSlot* PanelSlot : Slots)
	{
		if (UHorizontalBoxExSlot* TypedSlot = Cast<UHorizontalBoxExSlot>(PanelSlot))
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
