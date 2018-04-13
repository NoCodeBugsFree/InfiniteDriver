// Only 3dMotive and Crocopede has permission to redistribuite this project and all of its contents.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehicle.h"
#include "Truck.generated.h"

/** screen message FX  */
UENUM(BlueprintType)
enum class EMessageType : uint8
{
	MT_POOF			UMETA(DisplayName = "POOF"),
	MT_COIN			UMETA(DisplayName = "COIN"),
	MT_REPAIR		UMETA(DisplayName = "REPAIR"),
	MT_POWERUP		UMETA(DisplayName = "POWERUP")
};

/**
 * 
 */
UCLASS()
class INFINITEDRIVER_API ATruck : public AWheeledVehicle
{
	GENERATED_BODY()
	
	/** camera boom  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/* camera component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	/** static mesh component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ShadowMesh;
	
	/* Sweeper box collision  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* Sweeper;
	
	/* box collision  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* Overlapper;

	/* arrow component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* GameoverCameraLocation;
	
public:

	/** called to camera blend and end the game */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Gameplay")
	void GameOver();

	/** called to spawn Poof FX */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Gameplay")
	void SpawnScreenFX(EMessageType MessageType = EMessageType::MT_POOF);

	/** called to add some coins */
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void AddCoins() { Coins++; }

	/** called to repair the truck */
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void Repair(float Amount) { Health = FMath::Clamp(Health + Amount, 0.f, 100.f); }

	/** called to become invulnerable for 5 sec */
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void PowerUp();

	/** Coins amount  */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	int32 Coins = 0;

	/** distance   */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	float Distance = 0;
	
protected:

	ATruck();

	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	/** Apply damage to this actor */
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
private:

	/** Calculate Distance  */
	void CalcDistance(float DeltaSeconds);
	
	void HandBreakPressed();

	void HandBreakReleased();

	void MoveRight(float Value);

	/** invulnerable time  */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	float PowerupDelay = 10.f;

	/** shows whether car is invulnerable to crushes or not  */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	uint32 bPowerUp : 1;

	/** Health amount  */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	float Health = 100.f;

	/** Game Mode reference  */
	UPROPERTY(BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	class AInfiniteDriverGM* GM;

	/** called to perform level clean - up   */
	UFUNCTION()
	void OnSweeperOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	/** called to handle all available car collisions  */
	UFUNCTION()
	void OnOverlapperOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

public:
	
	/** returns current Health amount **/
	FORCEINLINE float GetHealth() const { return Health; }
	/** returns current Coins amount **/
	FORCEINLINE float GetCoins() const { return Coins; }
	/** returns current Distance amount **/
	FORCEINLINE float GetDistance() const { return Distance; }
};
