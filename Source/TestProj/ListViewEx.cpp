// Fill out your copyright notice in the Description page of Project Settings.


#include "ListViewEx.h"

UListViewEx::UListViewEx(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}


void UListViewEx::OnListViewScrolledInternal(float ItemOffset, float DistanceRemaining)
{
	BP_OnListViewScrolled.Broadcast(ItemOffset, DistanceRemaining);
}

UUserWidget& UListViewEx::OnGenerateEntryWidgetInternal(UObject* Item, TSubclassOf<UUserWidget> DesiredEntryClass,
	const TSharedRef<STableViewBase>& OwnerTable)
{
	if (OnGetEntryWidgetEvent.IsBound())
	{
		TSubclassOf<UUserWidget> CustomEntryClass = OnGetEntryWidgetEvent.Execute(Item);
		if (CustomEntryClass)
		{
			return GenerateTypedEntry(CustomEntryClass, OwnerTable);
		}
	}
	return GenerateTypedEntry(DesiredEntryClass, OwnerTable);
}