// Fill out your copyright notice in the Description page of Project Settings.


#include "TestProjLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

FString UTestProjLibrary::GetConfig(const FString& Section, const FString& Key, const FString& Path)
{
	FString Result;
	FString UserDir = UKismetSystemLibrary::GetPlatformUserDir();
	GConfig->GetString(*Section, *Key, Result, FPaths::Combine(UserDir, Path));
	return Result;
}

// const TCHAR* Section, const TCHAR* Key, const TCHAR* Value, const FString& Filename 
void UTestProjLibrary::SetConfig(const FString& Section, const FString& Key, const FString& Value, const FString& Path)
{
	FString UserDir = UKismetSystemLibrary::GetPlatformUserDir();
	GConfig->SetString(*Section, *Key, *Value, FPaths::Combine(UserDir, Path));
	GConfig->Flush(false, GGameUserSettingsIni);
}
