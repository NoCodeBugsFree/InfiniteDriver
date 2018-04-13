// Only 3dMotive and Crocopede has permission to redistribuite this project and all of its contents.

#include "Truck.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ConstructorHelpers.h"
#include "Components/BoxComponent.h"
#include "WheeledVehicleMovementComponent.h"
#include "TruckWheelFront.h"
#include "TruckWheelBack.h"
#include "Tile.h"
#include "InfiniteDriverGM.h"
#include "PickupBase.h"
#include "Sedan.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"

ATruck::ATruck()
{
	PrimaryActorTick.bCanEverTick = true;

	/**  set truck mesh */
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> TruckMeshTemplate(TEXT("/Game/TrucknTrailer/TrucknTrailerSkel"));
	if (TruckMeshTemplate.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(TruckMeshTemplate.Object);
	}
	GetMesh()->CastShadow = false;

	/** camera boom  */
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetRelativeLocation(FVector(-275.f, 0.f, 0.f));
	CameraBoom->TargetArmLength = 3000.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritRoll = false;
	CameraBoom->bInheritYaw = false;
	CameraBoom->bDoCollisionTest = false;

	/* camera component  */
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	CameraComponent->SetupAttachment(CameraBoom);
	CameraComponent->SetFieldOfView(75.f);
	CameraComponent->bConstrainAspectRatio = true;
	CameraComponent->AspectRatio = 0.6f;
	CameraComponent->SetRelativeRotation(FRotator(10.f, 0.f, 0.f));
	
	/** mesh  */
	ShadowMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShadowMesh"));
	ShadowMesh->SetupAttachment(RootComponent);
	ShadowMesh->SetRelativeScale3D(FVector(12.f, 4.f, 0.f));
	ShadowMesh->SetRelativeLocation(FVector(-490.f, 105.f, 20.f));

	/* arrow component  */
	GameoverCameraLocation = CreateDefaultSubobject<UArrowComponent>(TEXT("GameoverCameraLocation"));
	GameoverCameraLocation->SetupAttachment(RootComponent);

	/**  set the default static mesh */
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShadowMeshTemplate(TEXT("/Game/Scenery/ShadowPlane"));
	if (ShadowMeshTemplate.Succeeded())
	{
		ShadowMesh->SetStaticMesh(ShadowMeshTemplate.Object);
	}

	/* Sweeper box collision  */
	Sweeper = CreateDefaultSubobject<UBoxComponent>(TEXT("Sweeper"));
	Sweeper->SetupAttachment(RootComponent);
	Sweeper->SetBoxExtent(FVector(250.f, 2500.f, 1000.f));
	Sweeper->SetRelativeLocation(FVector(-10000.f, 0.f, 0.f));
	Sweeper->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	
	/* Overlapper box collision  */
	Overlapper = CreateDefaultSubobject<UBoxComponent>(TEXT("Overlapper"));
	Overlapper->SetupAttachment(RootComponent);
	Overlapper->SetBoxExtent(FVector(700.f, 150.f, 115.f));
	Overlapper->SetRelativeLocation(FVector(-450.f, 0.f, 150.f));
	Overlapper->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	// -----------------------------------------------------------------------------------
	//			setup Vehicle Movement comp
	// -----------------------------------------------------------------------------------

	/** setup wheel classes  */
	GetVehicleMovement()->WheelSetups[0].WheelClass = UTruckWheelFront::StaticClass();
	GetVehicleMovement()->WheelSetups[1].WheelClass = UTruckWheelFront::StaticClass();
	GetVehicleMovement()->WheelSetups[2].WheelClass = UTruckWheelBack::StaticClass();
	GetVehicleMovement()->WheelSetups[3].WheelClass = UTruckWheelBack::StaticClass();

	/** setup bone names  */
	GetVehicleMovement()->WheelSetups[0].BoneName = "Wheel_FR";
	GetVehicleMovement()->WheelSetups[1].BoneName = "Wheel_FL";
	GetVehicleMovement()->WheelSetups[2].BoneName = "WheelBR2";
	GetVehicleMovement()->WheelSetups[3].BoneName = "WheelBL2";

	GetVehicleMovement()->Mass = 1500.f;
	GetVehicleMovement()->DragCoefficient = 0.6f;
	GetVehicleMovement()->MaxEngineRPM = 10000.f;
	GetVehicleMovement()->SetUpdateNavAgentWithOwnersCollisions(false);

	bPowerUp = false;
}

void ATruck::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Sweeper->OnComponentEndOverlap.AddDynamic(this, &ATruck::OnSweeperOverlapEnd);
	Overlapper->OnComponentBeginOverlap.AddDynamic(this, &ATruck::OnOverlapperOverlapBegin);
}

void ATruck::BeginPlay()
{
	Super::BeginPlay();

	/** set GM reference  */
	if(AInfiniteDriverGM* TestGM = Cast<AInfiniteDriverGM>(GetWorld()->GetAuthGameMode()))
	{
		GM = TestGM;
	}
}

void ATruck::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CalcDistance(DeltaSeconds);

	/** move forward forever  */
	if (GetVehicleMovement()->GetForwardSpeed() <= 3000.f)
	{
		GetVehicleMovement()->SetThrottleInput(1.f);
	}
}

void ATruck::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/**  HandBreak  */
	PlayerInputComponent->BindAction("HandBreak", IE_Pressed, this, &ATruck::HandBreakPressed);
	PlayerInputComponent->BindAction("HandBreak", IE_Released, this, &ATruck::HandBreakReleased);

	/** move left/right  */
	PlayerInputComponent->BindAxis("MoveRight", this, &ATruck::MoveRight);
}

float ATruck::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	if (ActualDamage > 0.f)
	{
		Health -= ActualDamage;
		// If the damage depletes our health set our lifespan to zero - which will destroy the actor  
		if (Health <= 0.f)
		{
			GameOver();
		}
	}

	return ActualDamage;
}

void ATruck::CalcDistance(float DeltaSeconds)
{
	float ThisFrameDistance = DeltaSeconds * GetVelocity().Size() / 100.f;
	Distance += ThisFrameDistance;
}

void ATruck::HandBreakPressed()
{
	GetVehicleMovement()->SetHandbrakeInput(true);
}

void ATruck::HandBreakReleased()
{
	GetVehicleMovement()->SetHandbrakeInput(false);
}

void ATruck::MoveRight(float Value)
{
	GetVehicleMovement()->SetSteeringInput(Value * 0.1f);
}

void ATruck::OnSweeperOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != this)
	{
		if (ATile* Tile = Cast<ATile>(OtherActor))
		{
			if (Tile->IsActive())
			{
				Tile->SetActive(false);
				Tile->SetLifeSpan(5.f);
				/** spawn new tile  */
				if (GM)
				{
					GM->SpawnTile(); /** TODO prevent multi spawning */
				}
			}
		}
	}
}

void ATruck::OnOverlapperOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// Other Actor is the actor that triggered the event. Check that is not ourself. 
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && !OtherComp->IsPendingKill())
	{
		/** Pickup  */
		if (OtherActor->IsA(APickupBase::StaticClass()))
		{
			if(APickupBase* Pickup = Cast<APickupBase>(OtherActor))
			{
				Pickup->OnPickup(this);
			}
		}

		/** Sedan  */
		if (OtherActor->IsA(ASedan::StaticClass()))
		{
			if (ASedan* Sedan = Cast<ASedan>(OtherActor))
			{
				if ( ! bPowerUp )
				{
					/** apply damage  */
					float BaseDamage = Sedan->GetDamageToCause();
					UGameplayStatics::ApplyDamage(this, BaseDamage, nullptr, Sedan, UDamageType::StaticClass());
				}
				
				/** HUD Poof FX */
				SpawnScreenFX();

				/** temporarily disable sedan before destroy to prevent physics bugs */
				Sedan->SetActorEnableCollision(false);
				Sedan->SetActorHiddenInGame(true);

				/** actually destroy  */
				Sedan->Destroy();
			}
		}
	}
}

void ATruck::PowerUp()
{
	bPowerUp = true;

	FTimerDelegate PowerUpDelegate;
	PowerUpDelegate.BindLambda([&] { bPowerUp = false;  });
	
	FTimerHandle PowerUpTimer;
	GetWorldTimerManager().SetTimer(PowerUpTimer, PowerUpDelegate, PowerupDelay, false);
}
