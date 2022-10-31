// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GridNode.generated.h"

class AGridMap;
class AActor;

/*棋格坐标*/
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

	//重载运算符==，满足TMap中Key的规范
	FORCEINLINE friend bool operator==(const FGridVector& Lhs, const FGridVector& Rhs)
	{
		return (Lhs.X == Rhs.X) && (Lhs.Y == Rhs.Y);
	}

	//重载运算符+，满足基本加法运算
	FGridVector operator+ (const FGridVector& F)
	{
		return FGridVector(this->X + F.X, this->Y + F.Y);
	}

};

//GetTypeHash，满足TMap中Key的规范
FORCEINLINE uint32 GetTypeHash(const FGridVector& Key)
{
	return HashCombine(GetTypeHash(Key.X), GetTypeHash(Key.Y));
}

UCLASS()
class TESTPROJ_API UGridNode : public UObject
{
	GENERATED_BODY()

public:
	//基础-棋格大小
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Size;

	//基础-世界空间坐标
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector Location;

	//基础-棋盘空间坐标
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FGridVector Coordinate;

	//基础-所属棋盘
	UPROPERTY(BlueprintReadWrite)
		AGridMap* GridMap;

	//基础-初始化函数
	UFUNCTION(BlueprintCallable)
		void InitNode(AGridMap* InGridMap, FVector InLocation, FGridVector InCoordinate, float InSize);

	//基础-右上棋格
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UGridNode* RightUpNode;

	//基础-右棋格
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UGridNode* RightNode;

	//基础-右下棋格
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UGridNode* RightDownNode;

	//基础-左下棋格
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UGridNode* LeftDownNode;

	//基础-左棋格
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UGridNode* LeftNode;

	//基础-左上棋格
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UGridNode* LeftUpNode;

	//基础-获取相邻棋格
	UFUNCTION(BlueprintCallable)
		TArray<UGridNode*> GetNeighbors();

	//模型-棋格模型索引
	UPROPERTY()
		int MeshIndex;

	//模型-绘制模型
	UFUNCTION()
		void DrawNode(TArray<FVector>& InVertices,
			TArray<int32>& InIndecies,
			TArray<FVector>& InNormals,
			TArray<FVector2D>& InUV,
			TArray<FColor>& InVertexColors,
			TArray<FVector>& InTangents,
			FVector InOffset);
};
