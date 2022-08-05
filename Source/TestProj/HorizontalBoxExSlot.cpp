// Fill out your copyright notice in the Description page of Project Settings.


#include "HorizontalBoxExSlot.h"
#include "Components/Widget.h"

/////////////////////////////////////////////////////
// UHorizontalBoxExSlot

UHorizontalBoxExSlot::UHorizontalBoxExSlot(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bIsCustomLayout = false;
	HorizontalAlignment = HAlign_Fill;
	VerticalAlignment = VAlign_Fill;
	Raw_HorizontalAlignment = HAlign_Fill;
	Raw_VerticalAlignment = VAlign_Fill;
	Slot = NULL;
	Size = FSlateChildSize(ESlateSizeRule::Automatic);
	Raw_Size = FSlateChildSize(ESlateSizeRule::Automatic);
}

void UHorizontalBoxExSlot::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	Slot = NULL;
}

void UHorizontalBoxExSlot::BuildSlot(TSharedRef<SHorizontalBox> HorizontalBox)
{
	Slot = &HorizontalBox->AddSlot()
		.HAlign(bIsCustomLayout ? HorizontalAlignment : Raw_HorizontalAlignment)
		.VAlign(bIsCustomLayout ? VerticalAlignment : Raw_VerticalAlignment)
		.Padding(bIsCustomLayout ? Padding : Raw_Padding)
		[
			Content == NULL ? SNullWidget::NullWidget : Content->TakeWidget()
		];

	Slot->SizeParam = UWidget::ConvertSerializedSizeParamToRuntime(bIsCustomLayout ? Size : Raw_Size);
}

void UHorizontalBoxExSlot::SetPadding(FMargin InPadding)
{
	Padding = InPadding;
	UpdateSlotPadding();
}

void UHorizontalBoxExSlot::SetSize(FSlateChildSize InSize)
{
	Size = InSize;
	UpdateSlotSize();
}

void UHorizontalBoxExSlot::SetHorizontalAlignment(EHorizontalAlignment InHorizontalAlignment)
{
	HorizontalAlignment = InHorizontalAlignment;
	UpdateSlotHorizontalAlignment();
}

void UHorizontalBoxExSlot::SetVerticalAlignment(EVerticalAlignment InVerticalAlignment)
{
	VerticalAlignment = InVerticalAlignment;
	UpdateSlotVerticalAlignment();
}

//Update
void UHorizontalBoxExSlot::UpdateSlotPadding()
{
	if (Slot)
	{
		Slot->Padding(bIsCustomLayout ? Padding : Raw_Padding);
	}
}

void UHorizontalBoxExSlot::UpdateSlotSize()
{
	if (Slot)
	{
		Slot->SizeParam = UWidget::ConvertSerializedSizeParamToRuntime(bIsCustomLayout ? Size : Raw_Size);
	}
}

void UHorizontalBoxExSlot::UpdateSlotHorizontalAlignment()
{
	if (Slot)
	{
		Slot->HAlign(bIsCustomLayout ? HorizontalAlignment : Raw_HorizontalAlignment);
	}
}

void UHorizontalBoxExSlot::UpdateSlotVerticalAlignment()
{
	if (Slot)
	{
		Slot->VAlign(bIsCustomLayout ? VerticalAlignment : Raw_VerticalAlignment);
	}
}

void UHorizontalBoxExSlot::SynchronizeProperties()
{
	UpdateSlotPadding();
	UpdateSlotSize();
	UpdateSlotHorizontalAlignment();
	UpdateSlotVerticalAlignment();
}
