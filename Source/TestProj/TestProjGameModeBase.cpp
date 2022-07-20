// Copyright Epic Games, Inc. All Rights Reserved.


#include "TestProjGameModeBase.h"
#include "UnLua.h"

bool ATestProjGameModeBase::ProcessConsoleExec(const TCHAR* Cmd, FOutputDevice& Ar, UObject* Executor)
{
	UnLua::FLuaEnv Env;
	const auto bSuccess = Env.DoString("require 'ProcessConsoleExec'");
	check(bSuccess);

	FString sCmd = Cmd;
	const auto RetValues = UnLua::CallTableFunc(Env.GetMainState(), "_G", "ProcessConsoleExec", sCmd);
	check(RetValues.Num() == 1);

	const bool bHandle = RetValues[0].Value<bool>();
	return bHandle;
}
