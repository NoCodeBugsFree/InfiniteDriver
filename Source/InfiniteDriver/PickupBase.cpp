// Only 3dMotive and Crocopede has permission to redistribuite this project and all of its contents.

#include "PickupBase.h"
#include "ConstructorHelpers.h"
#include "Components/SphereComponent.h"

APickupBase::APickupBase()
{
	PrimaryActorTick.bCanEverTick = false;

	/* sphere collision  */
	Root = CreateDefaultSubobject<USphereComponent>(TEXT("Root"));
	SetRootComponent(Root);
	Root->SetSphereRadius(100.f);
	Root->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Root->SetCollisionProfileName("OverlapOnlyPawn");

	/**  set the Shadow static mesh */
	GetStaticMeshComponent()->SetupAttachment(RootComponent);
	GetStaticMeshComponent()->CastShadow = false;
	GetStaticMeshComponent()->SetRelativeLocation(FVector(0.f, 0.f, 60.f));
	GetStaticMeshComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CoinTemplate(TEXT("/Game/Pickups/Coin"));
	if (CoinTemplate.Succeeded())
	{
		GetStaticMeshComponent()->SetStaticMesh(CoinTemplate.Object);
	}

	/** Shadow mesh  */
	Shadow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shadow"));
	Shadow->SetupAttachment(RootComponent);
	Shadow->CastShadow = false;
	Shadow->SetRelativeLocation(FVector(0.f, 0.f, -40.f));
	Shadow->SetMobility(EComponentMobility::Movable);
	Shadow->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	/**  set the Shadow static mesh */
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShadowTemplate(TEXT("/Game/Scenery/ShadowPlane"));
	if (ShadowTemplate.Succeeded())
	{
		Shadow->SetStaticMesh(ShadowTemplate.Object);
	}
}

void APickupBase::OnPickup_Implementation(AActor* Pickuper)
{
	Destroy();
}
