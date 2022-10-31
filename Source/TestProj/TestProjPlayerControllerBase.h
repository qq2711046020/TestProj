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

	//����-������-����
	virtual void SetupInputComponent() override;

	//����-��ǰ����
	UPROPERTY(BlueprintReadWrite)
		AGridMap* BattleMap;

	//����-��ȡ����
	UFUNCTION(BlueprintCallable)
		AGridMap* GetBattleMap();

	//����-��ȡ����Ӧ���̵�λ��
	UFUNCTION(BlueprintCallable)
		FVector GetMouseCursorPosition() const;

	//����-����¼�
	UFUNCTION()
		void HandleLeftClick();
};
