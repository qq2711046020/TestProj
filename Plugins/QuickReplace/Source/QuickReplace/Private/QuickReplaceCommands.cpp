// Copyright Epic Games, Inc. All Rights Reserved.

#include "QuickReplaceCommands.h"

#define LOCTEXT_NAMESPACE "FQuickReplaceModule"

void FQuickReplaceCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "QuickReplace", "Execute QuickReplace action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
