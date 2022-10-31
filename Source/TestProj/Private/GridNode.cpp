// Fill out your copyright notice in the Description page of Project Settings.


#include "GridNode.h"
#include "GridMap.h"

void UGridNode::InitNode(AGridMap* InGridMap, FVector InLocation, FGridVector InCoordinate, float InSize)
{
	GridMap = InGridMap;
	Location = InLocation;
	Coordinate = InCoordinate;
	Size = InSize;
}

TArray<UGridNode*> UGridNode::GetNeighbors()
{
	TArray<UGridNode*> tNodes;
	if (RightUpNode)
		tNodes.Add(RightUpNode);
	if (RightNode)
		tNodes.Add(RightNode);
	if (RightDownNode)
		tNodes.Add(RightDownNode);
	if (LeftDownNode)
		tNodes.Add(LeftDownNode);
	if (LeftNode)
		tNodes.Add(LeftNode);
	if (LeftUpNode)
		tNodes.Add(LeftUpNode);
	return tNodes;
}

void UGridNode::DrawNode(TArray<FVector>& InVertices,
	TArray<int32>& InIndecies,
	TArray<FVector>& InNormals,
	TArray<FVector2D>& InUV,
	TArray<FColor>& InVertexColors,
	TArray<FVector>& InTangents,
	FVector InOffset)
{
	//顶点
	TArray<FVector> Verts;
	Verts.AddUninitialized(4);
	Verts[0] = Location - InOffset;
	Verts[1] = FVector(0, Size, 0) + Location - InOffset;
	Verts[2] = FVector(Size, Size, 0) + Location - InOffset;
	Verts[3] = FVector(Size, 0, 0) + Location - InOffset;

	//顶点索引
	TArray<int32> Indices;
	Indices.AddUninitialized(6);
	Indices[0] = 0; Indices[1] = 1; Indices[2] = 2;
	Indices[3] = 0; Indices[4] = 2; Indices[5] = 3;

	//法线
	TArray<FVector> Normals;
	Normals.Init(FVector(0, 0, 1), 4);
	//UV
	TArray<FVector2D> UV;
	UV.Init(FVector2D(0.f, 0.f), 4);
	UV[1] += FVector2D(0.f, 1.f);
	UV[2] += FVector2D(1.f, 1.f);
	UV[3] += FVector2D(1.f, 0.f);

	//顶点颜色
	TArray<FColor> VertexColors;
	VertexColors.Init(FColor::White, 4);
	//切线
	TArray<FVector> Tangents;
	Tangents.Init(FVector(1, 0, 0), 4);
	//回传
	InVertices = Verts;
	InIndecies = Indices;
	InNormals = Normals;
	InUV = UV;
	InVertexColors = VertexColors;
	InTangents = Tangents;
}