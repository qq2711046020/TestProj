// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TestProjPlayerControllerBase.generated.h"

class AGridMap;
class UGridNode;
/**
 * 
 */
UCLASS()
class TESTPROJ_API ATestProjPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	ATestProjPlayerControllerBase();

	//基础-绑定输入-覆盖
	virtual void SetupInputComponent() override;

	//基础-当前棋盘
	UPROPERTY(BlueprintReadWrite)
		AGridMap* BattleMap;

	//基础-获取棋盘
	UFUNCTION(BlueprintCallable)
		AGridMap* GetBattleMap();

	//基础-获取鼠标对应棋盘的位置
	UFUNCTION(BlueprintCallable)
		FVector GetMouseCursorPosition() const;

	//基础-左键事件
	UFUNCTION()
		void HandleLeftClick();
};
