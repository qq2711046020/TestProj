// Fill out your copyright notice in the Description page of Project Settings.

#include "TestProjPlayerControllerBase.h"
#include "EngineUtils.h"
#include "GridMap.h"

ATestProjPlayerControllerBase::ATestProjPlayerControllerBase()
{
	this->bShowMouseCursor = true;
}

void ATestProjPlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("LeftClick", IE_Pressed, this, &ATestProjPlayerControllerBase::HandleLeftClick);
}

AGridMap* ATestProjPlayerControllerBase::GetBattleMap()
{
	if (BattleMap)
		return BattleMap;
	//ʹ�õ���������
	for (TActorIterator<AGridMap> It(GetWorld()); It; ++It)
	{
		if (!*It)
			continue;
		BattleMap = *It;
		break;
	}
	return BattleMap;
}

FVector ATestProjPlayerControllerBase::GetMouseCursorPosition() const
{
	if (!BattleMap)
		return FVector::ZeroVector;
	FVector WorldLocation, WorldDirection;
	//��Ļ����ת�������꣬�ش�����ͷ���
	if (DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
	{
		//��ȡZ���ֵ
		float tScale = BattleMap->GetActorLocation().Z - WorldLocation.Z;
		tScale /= WorldDirection.Z;
		WorldLocation += tScale * WorldDirection;
		return WorldLocation;
	}
	return FVector::ZeroVector;
}

void ATestProjPlayerControllerBase::HandleLeftClick()
{
	if (!GetBattleMap())
		return;
	UGridNode* tHitNode = BattleMap->CheckHitNode(GetMouseCursorPosition());
	if (tHitNode)
	{
		BattleMap->SetNodeMaterial(tHitNode, BattleMap->BlockMaterial);
	}
}
