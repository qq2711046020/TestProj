// Fill out your copyright notice in the Description page of Project Settings.


#include "HorizontalBoxEx.h"
#include "Components/HorizontalBoxSlot.h"

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

UHorizontalBoxSlot* UHorizontalBoxEx::AddChildToHorizontalBoxEx(UWidget* Content)
{
	UHorizontalBoxSlot* ChildSlot = Cast<UHorizontalBoxSlot>(Super::AddChild(Content));
	ChildSlot->SetPadding(Padding);
	ChildSlot->SetSize(Size);
	ChildSlot->SetHorizontalAlignment(HorizontalAlignment);
	ChildSlot->SetVerticalAlignment(VerticalAlignment);
	return ChildSlot;
}

void UHorizontalBoxEx::OnSlotAdded(UPanelSlot* InSlot)
{
	// Add the child to the live canvas if it already exists
	if (MyHorizontalBox.IsValid())
	{
		UHorizontalBoxSlot* ChildSlot = Cast<UHorizontalBoxSlot>(InSlot);
		ChildSlot->BuildSlot(MyHorizontalBox.ToSharedRef());
		ChildSlot->SetPadding(Padding);
		ChildSlot->SetSize(Size);
		ChildSlot->SetHorizontalAlignment(HorizontalAlignment);
		ChildSlot->SetVerticalAlignment(VerticalAlignment);
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