// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEditorUtilityWidget.h"
#include "Editor.h"
#include "EditorAssetLibrary.h"
#include "WidgetBlueprint.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/TextBlock.h"

void UMyEditorUtilityWidget::UpdateAllTextFont(const FString& RootPath)
{
	TArray<FString> Files = UEditorAssetLibrary::ListAssets(RootPath);
	for (auto& AssetPath : Files)
	{
		if (UWidgetBlueprint* WidgetBlueprint = Cast<UWidgetBlueprint>(UEditorAssetLibrary::LoadAsset(AssetPath)))
		{
			bool isChange;
			TArray<UWidget*> Widgets;
			WidgetBlueprint->WidgetTree->GetAllWidgets(Widgets);
			for (UWidget* Widget : Widgets)
			{
				if (UTextBlock* Text = Cast<UTextBlock>(Widget))
				{
					if (ProcessTextWidget(Text))
					{
						isChange = true;
					}
				}
			}
			if (isChange)
			{
				UEditorAssetLibrary::SaveLoadedAsset(WidgetBlueprint);
			}
		}
	}
}
