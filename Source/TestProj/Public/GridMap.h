// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridNode.h"
#include "GridMap.generated.h"

class UProceduralMeshComponent;
class UMaterial;

UCLASS(hideCategories = (Materials))
class TESTPROJ_API AGridMap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridMap();

	//基础-棋盘单位大小
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Size;

	//基础-棋盘行数
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Roll;

	//基础-棋盘列数
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Colume;

	//基础-棋盘的棋格
	UPROPERTY()
		TMap<FGridVector, UGridNode*> NodeMap;

	//基础-生成棋盘
	UFUNCTION(BlueprintCallable)
		void GenerateGridMap();

	//基础-生成棋格入口
	UFUNCTION()
		void GenerateNodes(float InSize, int InRoll, int InColume);


	//基础-初始化棋格入口
	UFUNCTION()
		void InitNodes();

	//基础-获取坐标棋格
	UFUNCTION(BlueprintCallable)
		UGridNode* GetNode(FGridVector InCoord) const;

	//模型-棋盘模型
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UProceduralMeshComponent* Mesh;

	//模型-通行材质
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterialInterface* PassMaterial;

	//模型-阻挡材质
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterialInterface* BlockMaterial;

	//模型-阻挡材质1
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterialInterface* DebugMaterial1;

	//模型-阻挡材质2
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterialInterface* DebugMaterial2;

	//模型-生成棋盘模型
	UFUNCTION(BlueprintCallable)
		void GenerateMapMesh();

	//模型-设置棋格材质
	UFUNCTION(BlueprintCallable)
		void SetNodeMaterial(UGridNode* InNode, UMaterialInterface* InMaterial);

	//模型-重置棋格材质
	UFUNCTION(BlueprintCallable)
		void ResetNodeMaterial(UGridNode* InNode);

	//模型-重置所有棋格材质
	UFUNCTION(BlueprintCallable)
		void ResetNodeMaterialAll();

	//基础-判断是否在棋格内
	UFUNCTION(BlueprintCallable)
		UGridNode* CheckHitNode(FVector InPosition);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitProperties() override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
