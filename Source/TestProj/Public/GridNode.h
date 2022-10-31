// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GridNode.generated.h"

class AGridMap;
class AActor;

/*�������*/
USTRUCT(BlueprintType)
struct  FGridVector
{
public:
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int X = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Y = 0;

	FGridVector() {};
	FGridVector(int InX, int InY)
	{
		this->X = InX;
		this->Y = InY;
	}

	//���������==������TMap��Key�Ĺ淶
	FORCEINLINE friend bool operator==(const FGridVector& Lhs, const FGridVector& Rhs)
	{
		return (Lhs.X == Rhs.X) && (Lhs.Y == Rhs.Y);
	}

	//���������+����������ӷ�����
	FGridVector operator+ (const FGridVector& F)
	{
		return FGridVector(this->X + F.X, this->Y + F.Y);
	}

};

//GetTypeHash������TMap��Key�Ĺ淶
FORCEINLINE uint32 GetTypeHash(const FGridVector& Key)
{
	return HashCombine(GetTypeHash(Key.X), GetTypeHash(Key.Y));
}

UCLASS()
class TESTPROJ_API UGridNode : public UObject
{
	GENERATED_BODY()

public:
	//����-����С
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Size;

	//����-����ռ�����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector Location;

	//����-���̿ռ�����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FGridVector Coordinate;

	//����-��������
	UPROPERTY(BlueprintReadWrite)
		AGridMap* GridMap;

	//����-��ʼ������
	UFUNCTION(BlueprintCallable)
		void InitNode(AGridMap* InGridMap, FVector InLocation, FGridVector InCoordinate, float InSize);

	//����-�������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UGridNode* RightUpNode;

	//����-�����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UGridNode* RightNode;

	//����-�������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UGridNode* RightDownNode;

	//����-�������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UGridNode* LeftDownNode;

	//����-�����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UGridNode* LeftNode;

	//����-�������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UGridNode* LeftUpNode;

	//����-��ȡ�������
	UFUNCTION(BlueprintCallable)
		TArray<UGridNode*> GetNeighbors();

	//ģ��-���ģ������
	UPROPERTY()
		int MeshIndex;

	//ģ��-����ģ��
	UFUNCTION()
		void DrawNode(TArray<FVector>& InVertices,
			TArray<int32>& InIndecies,
			TArray<FVector>& InNormals,
			TArray<FVector2D>& InUV,
			TArray<FColor>& InVertexColors,
			TArray<FVector>& InTangents,
			FVector InOffset);
};
