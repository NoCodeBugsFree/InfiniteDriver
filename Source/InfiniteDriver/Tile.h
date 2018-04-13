// Only 3dMotive and Crocopede has permission to redistribuite this project and all of its contents.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "Tile.generated.h"

UCLASS()
class INFINITEDRIVER_API ATile : public AActor
{
	GENERATED_BODY()

	/* scene ROOT component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* Root;

	/** Ground static mesh component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Ground;
	
	/** PowerLine static mesh component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* PowerLine;
	
	/* AttachPoint arrow component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* AttachPoint;

	/** static mesh component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BridgeM;
	
	/** static mesh component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BridgeR;
	
	/** static mesh component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BridgeL;

	/** static mesh component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BridgeShadow;

	/* spawn box */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* SpawnArea;

	/* border box 01 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* Border01;

	/* border box 02 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* Border02;
	
	/* Lane01 arrow component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* Lane01;

	/* Lane02 arrow component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* Lane02;

	/* Lane03 arrow component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* Lane03;

	/* Lane04 arrow component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* Lane04;

public:	

	/** called to set new active state  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SetActive(bool bNewActive) { bActive = bNewActive; }

protected:

	// Sets default values for this actor's properties
	ATile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	/** called to spawn pickups on this tile */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "AAA")
	void SpawnPickups();

	/** called to spawn cars */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "AAA")
	void SpawnCars();
	
private:

	/** shows whether this tile is active or not  */
	uint32 bActive : 1;

	/** called to  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	FVector GetRandomPointInVolume() const;
	
	/** pickups spawned by this tile  */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<class APickupBase>> Pickups;

public:	
	
	/** retunrs whether this tile is active or not **/
	FORCEINLINE bool IsActive() const { return bActive; }
	/** returns next attach point location **/
	FORCEINLINE FTransform GetNextAttachPoint() const { return AttachPoint->GetComponentTransform(); }
	
};
