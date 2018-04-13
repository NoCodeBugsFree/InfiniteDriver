// Only 3dMotive and Crocopede has permission to redistribuite this project and all of its contents.

#include "Sedan.h"
#include "ConstructorHelpers.h"
#include "Components/BoxComponent.h"
#include "WheeledVehicleMovementComponent.h"
#include "SedanWheelBack.h"
#include "SedanWheelFront.h"
#include "DrawDebugHelpers.h"

ASedan::ASedan()
{
	/**  set truck mesh */
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> TruckMeshTemplate(TEXT("/Game/Sedan/Sedan"));
	if (TruckMeshTemplate.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(TruckMeshTemplate.Object);
	}
	GetMesh()->CastShadow = false;

	/** shadow static mesh component  */
	ShadowMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShadowMesh"));
	ShadowMesh->SetupAttachment(RootComponent);
	ShadowMesh->SetRelativeScale3D(FVector(5.f, 3.f, 1.f));
	ShadowMesh->SetRelativeLocation(FVector(0.f, 40.f, 0.f));

	/**  set the default static mesh */
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShadowMeshTemplate(TEXT("/Game/Scenery/ShadowPlane"));
	if (ShadowMeshTemplate.Succeeded())
	{
		ShadowMesh->SetStaticMesh(ShadowMeshTemplate.Object);
	}

	/* Sweeper box collision  */
	CarCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Sweeper"));
	CarCollision->SetupAttachment(RootComponent);
	CarCollision->SetBoxExtent(FVector(330.f, 100.f, 75.f));
	CarCollision->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	CarCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	/** setup wheel classes  */
	GetVehicleMovement()->WheelSetups[0].WheelClass = USedanWheelFront::StaticClass();
	GetVehicleMovement()->WheelSetups[1].WheelClass = USedanWheelFront::StaticClass();
	GetVehicleMovement()->WheelSetups[2].WheelClass = USedanWheelBack::StaticClass();
	GetVehicleMovement()->WheelSetups[3].WheelClass = USedanWheelBack::StaticClass();

	/** setup bone names  */
	GetVehicleMovement()->WheelSetups[0].BoneName = "Sedan_FL";
	GetVehicleMovement()->WheelSetups[1].BoneName = "Sedan_FR";
	GetVehicleMovement()->WheelSetups[2].BoneName = "Sedan_BL";
	GetVehicleMovement()->WheelSetups[3].BoneName = "Sedan_BR";
	
	GetVehicleMovement()->SetUpdateNavAgentWithOwnersCollisions(false);
}

void ASedan::BeginPlay()
{
	Super::BeginPlay();

	ForwardVector = GetActorForwardVector();

	/** set throttle value for this car  */
	ThrottleValue = FMath::RandRange(0.5f, 1.f);

	/** set random color  */
	DynamicMaterial = GetMesh()->CreateDynamicMaterialInstance(0);
	if (DynamicMaterial)
	{
		DynamicMaterial->SetScalarParameterValue("HueShift", FMath::RandRange(0.f, 255.f));
	}

	// start left right timer
	FTimerDelegate LeftRightDelegate;
	LeftRightDelegate.BindLambda([&] { bLeft = FMath::RandBool();  });
	
	FTimerHandle LeftRightTimer;
	GetWorldTimerManager().SetTimer(LeftRightTimer, LeftRightDelegate, 3.f, true);
}

void ASedan::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	/** drive forever  */
	GetVehicleMovement()->SetThrottleInput(ThrottleValue);

	FVector Start = GetActorLocation() + FVector(100.f, 0.f, 50.f);
	FVector End = Start + GetActorForwardVector() * TraceDistance;

	FHitResult Hit;
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);

	FCollisionQueryParams CQP;
	CQP.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByObjectType(Hit, Start, End, ObjectQueryParams, CQP);

	// DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, DeltaSeconds * 3, 0, 10.f);

	if (Hit.bBlockingHit)  /** steer  */
	{
		if (bLeft)
		{
			SteeringValue = 1.f;
		}
		else
		{
			SteeringValue = -1.f;
		}
		SteeringValue *= FMath::RandRange(0.1f, 0.2f);
		GetVehicleMovement()->SetSteeringInput(SteeringValue);
		StopSteeringTimer.Invalidate();
	}
	else
	{
		/** StopSteering by timer */
		if ( ! StopSteeringTimer.IsValid() )
		{
			GetWorldTimerManager().SetTimer(StopSteeringTimer, this, &ASedan::StopSteering, FMath::RandRange(0.2f, 0.4f), false);
		}
		
		GetVehicleMovement()->SetSteeringInput(SteeringValue); /** move forward  */
	}
}

void ASedan::StopSteering()
{
	FVector UnrotatedVector = GetActorRotation().UnrotateVector(ForwardVector);
	SteeringValue = UnrotatedVector.Y;
}