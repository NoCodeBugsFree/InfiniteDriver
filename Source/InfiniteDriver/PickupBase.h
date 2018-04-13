// Only 3dMotive and Crocopede has permission to redistribuite this project and all of its contents.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "PickupBase.generated.h"

/**
 * 
 */
UCLASS()
class INFINITEDRIVER_API APickupBase : public AStaticMeshActor
{
	GENERATED_BODY()

	/** static mesh component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Shadow;

	/* sphere collision  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* Root;
	
public:

	/** called when this pickup is picked up */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gameplay")
	void OnPickup(AActor* Pickuper);
	virtual void OnPickup_Implementation(AActor* Pickuper);

protected:

	APickupBase();
	
};
