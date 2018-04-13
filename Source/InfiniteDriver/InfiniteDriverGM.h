// Only 3dMotive and Crocopede has permission to redistribuite this project and all of its contents.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "InfiniteDriverGM.generated.h"

/**
 * 
 */
UCLASS()
class INFINITEDRIVER_API AInfiniteDriverGM : public AGameModeBase
{
	GENERATED_BODY()
	
	/** Tile Template Class  */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ATile> TileClass;

public:

	/** called to spawn single level tile */
	UFUNCTION(BlueprintCallable, Category = "GamePlay")
	void SpawnTile();

protected:

	AInfiniteDriverGM();

	virtual void BeginPlay() override;

private:

	/** world space spawn point for next level tile  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	FTransform NextSpawnPoint;
	
	/** how many tiles we need to spawn at begin play  */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	int32 InitialTilesAmount = 4;
	
};
