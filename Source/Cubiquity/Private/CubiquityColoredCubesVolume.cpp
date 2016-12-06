// Copyright 2014 Volumes of Fun. All Rights Reserved.

#include "CubiquityPluginPrivatePCH.h"

#include "CubiquityColoredCubesVolume.h"

#include "CubiquityOctreeNode.h"
#include "CubiquityMeshComponent.h"

ACubiquityColoredCubesVolume::ACubiquityColoredCubesVolume(const FObjectInitializer& PCIP)
	: Super(PCIP)
{
	volumeFileName = "D:/Unreal Projects/FPSTemplate/Plugins/Cubiquity/example-vdb/VoxeliensTerrain.vdb";
}

void ACubiquityColoredCubesVolume::PostActorCreated()
{
	UE_LOG(CubiquityLog, Log, TEXT("ACubiquityColoredCubesVolume::PostActorCreated"));
	
	Super::PostActorCreated();
}

void ACubiquityColoredCubesVolume::PostLoad()
{
	UE_LOG(CubiquityLog, Log, TEXT("ACubiquityColoredCubesVolume::PostLoad"));

	Super::PostLoad();
}

void ACubiquityColoredCubesVolume::Destroyed()
{
	Super::Destroyed();

	m_volume.reset(nullptr);
}

void ACubiquityColoredCubesVolume::loadVolume()
{
	m_volume = loadVolumeImpl<Cubiquity::ColoredCubesVolume>();
}

FVector ACubiquityColoredCubesVolume::pickFirstSolidVoxel(FVector localStartPosition, FVector localDirection) const
{
	bool success;
	auto hitLocation = m_volume->pickFirstSolidVoxel({ localStartPosition.X, localStartPosition.Y, localStartPosition.Z }, { localDirection.X, localDirection.Y, localDirection.Z }, &success);

	if (!success)
	{
		UE_LOG(CubiquityLog, Log, TEXT("Surface pick found nothing"));
		return FVector::ZeroVector;
	}

	return FVector(hitLocation.x, hitLocation.y, hitLocation.z);
}

FVector ACubiquityColoredCubesVolume::pickLastEmptyVoxel(FVector localStartPosition, FVector localDirection) const
{
	bool success;
	auto hitLocation = m_volume->pickLastEmptyVoxel({ localStartPosition.X, localStartPosition.Y, localStartPosition.Z }, { localDirection.X, localDirection.Y, localDirection.Z }, &success);

	if (!success)
	{
		UE_LOG(CubiquityLog, Log, TEXT("Surface pick found nothing"));
		return FVector::ZeroVector;
	}

	return FVector(hitLocation.x, hitLocation.y, hitLocation.z);
}

void ACubiquityColoredCubesVolume::setVoxel(FVector position, FColor newColor)
{
	m_volume->setVoxel({ (int32_t)position.X, (int32_t)position.Y, (int32_t)position.Z }, { newColor.R, newColor.G, newColor.B, newColor.A });
}

FColor ACubiquityColoredCubesVolume::getVoxel(FVector position) const
{
	const auto& voxel = m_volume->getVoxel({ (int32_t)position.X, (int32_t)position.Y, (int32_t)position.Z });
	return {voxel.red(), voxel.green(), voxel.blue(), voxel.alpha()};
}
