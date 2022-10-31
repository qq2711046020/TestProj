// Fill out your copyright notice in the Description page of Project Settings.


#include "GridMap.h"
#include "GridNode.h"
#include "ProceduralMeshComponent.h"

// Sets default values
AGridMap::AGridMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Size = 100.f;
	Roll = 10;
	Colume = 10;

	Mesh = CreateDefaultSubobject<UProceduralMeshComponent>("MapMesh");
	this->SetRootComponent(Mesh);
}

void AGridMap::GenerateGridMap()
{
	for (auto a : NodeMap)
	{
		//标记垃圾回收
		if (a.Value)
			a.Value->MarkPendingKill();
	}
	//重置Map
	NodeMap.Reset();
	//重新生成棋格
	GenerateNodes(Size, Roll, Colume);
	//重新生成模型
	GenerateMapMesh();
}

void AGridMap::GenerateNodes(float InSize, int InRoll, int InColume)
{
	/*
	 *  |i
	 *  |
	 *  |
	 *  |
	 *  |0,0
	 *  +-------------------j
	 */
	FVector InnerLocation;
	for (int i = 0; i < InRoll; ++i)
	{
		for (int j = 0; j < InColume; ++j)
		{
			//UE中横向坐标轴为Y，纵向坐标轴为X，需要调换在二维坐标系XY的值
			FGridVector Coord = FGridVector(j, i);
			InnerLocation.X = InSize * i;
			InnerLocation.Y = InSize * j;
			InnerLocation.Z = 0;
			InnerLocation += GetActorLocation();
			UGridNode* tNode = NewObject<UGridNode>(this);
			//棋格初始化
			tNode->InitNode(this, InnerLocation, Coord, InSize);
			NodeMap.Add(Coord, tNode);
		}
	}

	InitNodes();
}

void AGridMap::InitNodes()
{
	for (auto a : NodeMap)
	{
		UGridNode* tNode = Cast<UGridNode>(a.Value);
		if (!tNode)
			continue;
		FGridVector tRightUp = a.Key + FGridVector(1, 1);
		if (NodeMap.Contains(tRightUp) && NodeMap[tRightUp]->IsA(UGridNode::StaticClass()))
			tNode->RightUpNode = Cast<UGridNode>(NodeMap[tRightUp]);

		FGridVector tRight = a.Key + FGridVector(1, 0);
		if (NodeMap.Contains(tRight) && NodeMap[tRight]->IsA(UGridNode::StaticClass()))
			tNode->RightNode = Cast<UGridNode>(NodeMap[tRight]);

		FGridVector tRightDown = a.Key + FGridVector(1, -1);
		if (NodeMap.Contains(tRightDown) && NodeMap[tRightDown]->IsA(UGridNode::StaticClass()))
			tNode->RightDownNode = Cast<UGridNode>(NodeMap[tRightDown]);

		FGridVector tLeftDown = a.Key + FGridVector(0, -1);
		if (NodeMap.Contains(tLeftDown) && NodeMap[tLeftDown]->IsA(UGridNode::StaticClass()))
			tNode->LeftDownNode = Cast<UGridNode>(NodeMap[tLeftDown]);

		FGridVector tLeft = a.Key + FGridVector(-1, 0);
		if (NodeMap.Contains(tLeft) && NodeMap[tLeft]->IsA(UGridNode::StaticClass()))
			tNode->LeftNode = Cast<UGridNode>(NodeMap[tLeft]);

		FGridVector tLeftUp =  a.Key + FGridVector(0, 1);
		if (NodeMap.Contains(tLeftUp) && NodeMap[tLeftUp]->IsA(UGridNode::StaticClass()))
			tNode->LeftUpNode = Cast<UGridNode>(NodeMap[tLeftUp]);

	}
}

UGridNode* AGridMap::GetNode(FGridVector InCoord) const
{
	if (NodeMap.Contains(InCoord))
		return NodeMap[InCoord];
	else
		return nullptr;
}

void AGridMap::GenerateMapMesh()
{
	//模型索引，表示棋格是Mesh上第几个分区
	int Index = 0;
	//重置
	Mesh->ClearAllMeshSections();
	for (auto a : NodeMap)
	{
		if (!a.Value)
			continue;
		TArray<FVector> Vertices;
		TArray<int32> Indecies;
		TArray<FVector> Normals;
		TArray<FVector2D> UV1, EmptyArray;
		TArray<FColor> VertexColors;
		TArray<FVector> Tangents;
		TArray<FProcMeshTangent> MeshTangents;
		//索引赋值
		a.Value->MeshIndex = Index;
		//调用DrawNode，以引用方式回传绘制信息
		a.Value->DrawNode(Vertices, Indecies, Normals, UV1, VertexColors, Tangents, GetActorLocation());
		//用切线向量生成切线结构体
		for (FVector& b : Tangents)
			MeshTangents.Add(FProcMeshTangent(b, false));
		//生成索引区块模型
		Mesh->CreateMeshSection(Index, Vertices, Indecies, Normals, UV1, EmptyArray, EmptyArray, EmptyArray, VertexColors, MeshTangents, false);
		//设置材质
		ResetNodeMaterial(a.Value);
		Index++;
	}
}

//设置模型材质
void AGridMap::SetNodeMaterial(UGridNode* InNode, UMaterialInterface* InMaterial)
{
	if (!InNode || !InMaterial)
		return;
	Mesh->SetMaterial(InNode->MeshIndex, InMaterial);
}

//重置模型材质
void AGridMap::ResetNodeMaterial(UGridNode* InNode)
{
	if (!InNode)
		return;
	SetNodeMaterial(InNode, PassMaterial);
}

//重置所有模型材质
void AGridMap::ResetNodeMaterialAll()
{
	for (auto a : NodeMap)
	{
		if (!a.Value)
			continue;
		ResetNodeMaterial(a.Value);
	}
}

//判断是否在棋格内
UGridNode* AGridMap::CheckHitNode(FVector InPosition)
{
	UGridNode* tHitNode = nullptr;
	if (FMath::Abs(InPosition.Z - GetActorLocation().Z) > 1)
		return tHitNode;
	float x = InPosition.X - GetActorLocation().X;
	float y = InPosition.Y - GetActorLocation().Y;
	FGridVector Coord = FGridVector(FMath::Floor(y / Size), FMath::Floor(x / Size));
	if (NodeMap.Contains(Coord) && NodeMap[Coord]->IsA(UGridNode::StaticClass()))
		tHitNode = Cast<UGridNode>(NodeMap[Coord]);
	return tHitNode;
}

// Called when the game starts or when spawned
void AGridMap::BeginPlay()
{
	Super::BeginPlay();
	GenerateGridMap();
	
}

void AGridMap::PostInitProperties()
{
	Super::PostInitProperties();
	GenerateGridMap();
}

#if WITH_EDITOR
//编辑器中改变属性时调用
void AGridMap::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	//当行、列、大小改变时重新生成棋盘
	//if (PropertyChangedEvent.Property->GetName() == "Roll"
	//	|| PropertyChangedEvent.Property->GetName() == "Colume"
	//	|| PropertyChangedEvent.Property->GetName() == "Size")
	//{
	//	GenerateGridMap();
	//}
}
#endif


// Called every frame
void AGridMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

