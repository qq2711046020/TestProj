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

	//����-���̵�λ��С
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Size;

	//����-��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Roll;

	//����-��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Colume;

	//����-���̵����
	UPROPERTY()
		TMap<FGridVector, UGridNode*> NodeMap;

	//����-��������
	UFUNCTION(BlueprintCallable)
		void GenerateGridMap();

	//����-����������
	UFUNCTION()
		void GenerateNodes(float InSize, int InRoll, int InColume);


	//����-��ʼ��������
	UFUNCTION()
		void InitNodes();

	//����-��ȡ�������
	UFUNCTION(BlueprintCallable)
		UGridNode* GetNode(FGridVector InCoord) const;

	//ģ��-����ģ��
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UProceduralMeshComponent* Mesh;

	//ģ��-ͨ�в���
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterialInterface* PassMaterial;

	//ģ��-�赲����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterialInterface* BlockMaterial;

	//ģ��-�赲����1
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterialInterface* DebugMaterial1;

	//ģ��-�赲����2
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterialInterface* DebugMaterial2;

	//ģ��-��������ģ��
	UFUNCTION(BlueprintCallable)
		void GenerateMapMesh();

	//ģ��-����������
	UFUNCTION(BlueprintCallable)
		void SetNodeMaterial(UGridNode* InNode, UMaterialInterface* InMaterial);

	//ģ��-����������
	UFUNCTION(BlueprintCallable)
		void ResetNodeMaterial(UGridNode* InNode);

	//ģ��-��������������
	UFUNCTION(BlueprintCallable)
		void ResetNodeMaterialAll();

	//����-�ж��Ƿ��������
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
