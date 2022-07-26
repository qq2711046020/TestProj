// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "QuickReplaceStyle.h"

class FQuickReplaceCommands : public TCommands<FQuickReplaceCommands>
{
public:

	FQuickReplaceCommands()
		: TCommands<FQuickReplaceCommands>(TEXT("QuickReplace"), NSLOCTEXT("Contexts", "QuickReplace", "QuickReplace Plugin"), NAME_None, FQuickReplaceStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
