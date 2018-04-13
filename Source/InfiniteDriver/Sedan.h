// Only 3dMotive and Crocopede has permission to redistribuite this project and all of its contents.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehicle.h"
#include "Sedan.generated.h"

/**
 * 
 */
UCLASS()
class INFINITEDRIVER_API ASedan : public AWheeledVehicle
{
	GENERATED_BODY()

	/** shadow static mesh component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ShadowMesh;

	/* Car Collision box collision  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* CarCollision;
	
	/** car's dynamic material  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	class UMaterialInstanceDynamic* DynamicMaterial;
	
protected:

	ASedan();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
private:

	/** damage to cause when crushed */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	float Damage = 20.f;

	/** shows whether we are steering left or right */
	uint32 bLeft : 1;
		
	UPROPERTY()
	FTimerHandle StopSteeringTimer;

	/** sets movement direction to  ForwardVector */
	void StopSteering();

	/** forward trace distance to start steering  */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	float TraceDistance = 3000.f;

	/** throttle for this car */
	UPROPERTY(BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	float ThrottleValue = 0.5f;

	/** steering for this car */
	UPROPERTY(BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	float SteeringValue = 0.f;
	
	/** initial forward vector  */
	FVector ForwardVector;

public:

	/** retunrs damage caused when crush  **/
	FORCEINLINE float GetDamageToCause() const { return Damage; }
	
};
