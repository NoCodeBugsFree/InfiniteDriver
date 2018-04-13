// Only 3dMotive and Crocopede has permission to redistribuite this project and all of its contents.

#include "Tile.h"
#include "Components/BoxComponent.h"
#include "ConstructorHelpers.h"
#include "PickupBase.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	/* scene component  */
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	/** ground mesh  */
	Ground = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ground"));
	Ground->SetupAttachment(RootComponent);
	Ground->CastShadow = false;
	Ground->bCastDynamicShadow = false;

	/**  set the ground mesh */
	static ConstructorHelpers::FObjectFinder<UStaticMesh> GroundTemplate(TEXT("/Game/Scenery/Plane"));
	if (GroundTemplate.Succeeded())
	{
		Ground->SetStaticMesh(GroundTemplate.Object);
	}

	/** Power line mesh  */
	PowerLine = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PowerLine"));
	PowerLine->SetupAttachment(RootComponent);
	PowerLine->CastShadow = false;
	PowerLine->bCastDynamicShadow = false;
	PowerLine->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PowerLine->SetRelativeLocation(FVector(0.f, -3000.f, 0.f));

	/**  set the Power line mesh */
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PowerLineTemplate(TEXT("/Game/Scenery/KragPaale"));
	if (PowerLineTemplate.Succeeded())
	{
		PowerLine->SetStaticMesh(PowerLineTemplate.Object);
	}

	/* AttachPoint arrow component  */
	AttachPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	AttachPoint->SetupAttachment(RootComponent);
	AttachPoint->SetRelativeLocation(FVector(10000.f, 0.f, 0.f));
	AttachPoint->ArrowSize = 15.f;

	/** Bridge mesh  */
	BridgeM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BridgeM"));
	BridgeM->SetupAttachment(RootComponent);
	BridgeM->SetRelativeLocation(FVector(4100.f, 0.f, 0.f));
	BridgeM->CastShadow = false;
	BridgeM->bCastDynamicShadow = false;

	/** BridgeR mesh  */
	BridgeR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BridgeR"));
	BridgeR->SetupAttachment(RootComponent);
	BridgeR->SetRelativeLocation(FVector(4100.f, 10000.f, 0.f));
	BridgeR->CastShadow = false;
	BridgeR->bCastDynamicShadow = false;

	/** BridgeR mesh  */
	BridgeL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BridgeL"));
	BridgeL->SetupAttachment(RootComponent);
	BridgeL->SetRelativeLocation(FVector(4100.f, -10000.f, 0.f));
	BridgeL->CastShadow = false;
	BridgeL->bCastDynamicShadow = false;

	/**  set the Bridge static mesh */
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BridgeMTemplate(TEXT("/Game/Scenery/Bridge"));
	if (BridgeMTemplate.Succeeded())
	{
		BridgeM->SetStaticMesh(BridgeMTemplate.Object);
		BridgeR->SetStaticMesh(BridgeMTemplate.Object);
		BridgeL->SetStaticMesh(BridgeMTemplate.Object);
	}

	/** Bridge Shadow mesh  */
	BridgeShadow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BridgeShadow"));
	BridgeShadow->SetupAttachment(RootComponent);
	BridgeShadow->SetRelativeLocation(FVector(3660.f, 0.f, 650.f));
	BridgeShadow->SetRelativeScale3D(FVector(33.f, 200.f, 0.f));
	BridgeShadow->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	/**  set the Bridge Shadow static mesh */
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BridgeShadowTemplate(TEXT("/Game/Scenery/ShadowPlane"));
	if (BridgeShadowTemplate.Succeeded())
	{
		BridgeShadow->SetStaticMesh(BridgeShadowTemplate.Object);
	}

	/* spawn box */
	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	SpawnArea->SetupAttachment(RootComponent);
	SpawnArea->SetBoxExtent(FVector(5000.f, 1800.f, 200.f));
	SpawnArea->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SpawnArea->SetRelativeLocation(FVector(5000.f, 0.f, 200.f));

	/* border box 01 */
	Border01 = CreateDefaultSubobject<UBoxComponent>(TEXT("Border01"));
	Border01->SetCollisionProfileName("BlockAll");
	Border01->SetupAttachment(RootComponent);
	Border01->SetBoxExtent(FVector(5000.f, 1800.f, 200.f));
	Border01->SetRelativeLocation(FVector(5000.f, 3600.f, 1000.f));

	/* border box 02 */
	Border02 = CreateDefaultSubobject<UBoxComponent>(TEXT("Border02"));
	Border02->SetCollisionProfileName("BlockAll");
	Border02->SetupAttachment(RootComponent);
	Border02->SetBoxExtent(FVector(5000.f, 1800.f, 200.f));
	Border02->SetRelativeLocation(FVector(5000.f, -3600.f, 1000.f));

	/* Lane01 arrow component  */
	Lane01 = CreateDefaultSubobject<UArrowComponent>(TEXT("Lane01"));
	Lane01->SetupAttachment(RootComponent);
	Lane01->SetRelativeLocation(FVector(8000.f, 1250.f, 0.f));
	Lane01->SetRelativeRotation(FRotator(0.f, -180.f, 0.f));
	Lane01->ArrowSize = 15.f;

	/* Lane02 arrow component  */
	Lane02 = CreateDefaultSubobject<UArrowComponent>(TEXT("Lane02"));
	Lane02->SetupAttachment(RootComponent);
	Lane02->SetRelativeLocation(FVector(9650.f, 520.f, 0.f));
	Lane02->SetRelativeRotation(FRotator(0.f, -180.f, 0.f));
	Lane02->ArrowSize = 15.f;

	/* Lane03 arrow component  */
	Lane03 = CreateDefaultSubobject<UArrowComponent>(TEXT("Lane03"));
	Lane03->SetupAttachment(RootComponent);
	Lane03->SetRelativeLocation(FVector(7000.f, -1430.f, 0.f));
	Lane03->ArrowSize = 15.f;

	/* Lane04 arrow component  */
	Lane04 = CreateDefaultSubobject<UArrowComponent>(TEXT("Lane04"));
	Lane04->SetupAttachment(RootComponent);
	Lane04->SetRelativeLocation(FVector(8460.f, -610.f, 0.f));
	Lane04->ArrowSize = 15.f;

	/** defaults  */
	bActive = true;
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();

	SpawnPickups();
	
	SpawnCars();
}

FVector ATile::GetRandomPointInVolume() const
{
	if (SpawnArea)
	{
		FVector SpawnOrigin = SpawnArea->Bounds.Origin;
		FVector SpawnExtent = SpawnArea->Bounds.BoxExtent;
		return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);
	}
	return FVector();
}

