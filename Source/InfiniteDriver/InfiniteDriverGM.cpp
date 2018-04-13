// Only 3dMotive and Crocopede has permission to redistribuite this project and all of its contents.

#include "InfiniteDriverGM.h"
#include "Tile.h"
#include "ConstructorHelpers.h"

AInfiniteDriverGM::AInfiniteDriverGM()
{
	/**  set tile class */
	static ConstructorHelpers::FClassFinder<ATile> TileTemplate(TEXT("/Game/MyBP/LevelGeometry/BP_Tile"));
	if (TileTemplate.Class)
	{
		TileClass = TileTemplate.Class;
	}
}

void AInfiniteDriverGM::BeginPlay()
{
	Super::BeginPlay();

	/** spawn initial tiles  */
	for (int i = 0; i < InitialTilesAmount; i++)
	{
		SpawnTile();
	}
}

void AInfiniteDriverGM::SpawnTile()
{
	if (TileClass)
	{
		UWorld* const World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator; //  GetController();
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			
			FTransform SpawnTransform = NextSpawnPoint;
			
			ATile* SpawnedTile = World->SpawnActor<ATile>(TileClass, NextSpawnPoint, SpawnParams);
			if (SpawnedTile)
			{
				NextSpawnPoint = SpawnedTile->GetNextAttachPoint();
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("TileClass == NULL"));
	}
}
