// Copyright Epic Games, Inc. All Rights Reserved.

#include "QuickReplace.h"
#include "QuickReplaceStyle.h"
#include "QuickReplaceCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include "Editor.h"
#include "EditorAssetLibrary.h"
#include "WidgetBlueprint.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/TextBlock.h"

static const FName QuickReplaceTabName("QuickReplace");

#define LOCTEXT_NAMESPACE "FQuickReplaceModule"

void FQuickReplaceModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FQuickReplaceStyle::Initialize();
	FQuickReplaceStyle::ReloadTextures();

	FQuickReplaceCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FQuickReplaceCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FQuickReplaceModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FQuickReplaceModule::RegisterMenus));
}

void FQuickReplaceModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FQuickReplaceStyle::Shutdown();

	FQuickReplaceCommands::Unregister();
}

void FQuickReplaceModule::PluginButtonClicked()
{
	FString DirectoryPath = "/Game/UI";
	TArray<FString> Files = UEditorAssetLibrary::ListAssets(DirectoryPath);
	for (auto& AssetPath : Files)
	{
		if (UWidgetBlueprint* WidgetBlueprint = Cast<UWidgetBlueprint>(UEditorAssetLibrary::LoadAsset(AssetPath)))
		{
			TArray<UWidget*> Widgets;
			WidgetBlueprint->WidgetTree->GetAllWidgets(Widgets);
			for (UWidget* Widget : Widgets)
			{
				if (UTextBlock* Text = Cast<UTextBlock>(Widget))
				{
					Text->SetText(FText());
				}
			}
			UEditorAssetLibrary::SaveLoadedAsset(WidgetBlueprint);
		}
	}
		
}

void FQuickReplaceModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FQuickReplaceCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FQuickReplaceCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FQuickReplaceModule, QuickReplace)