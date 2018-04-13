// Only 3dMotive and Crocopede has permission to redistribuite this project and all of its contents.

#include "InfiniteDriverHUD.h"
#include "Blueprint/UserWidget.h"
#include "ConstructorHelpers.h"
#include "InfiniteDriverWidget.h"
#include "Components/ProgressBar.h"
#include "Truck.h"
#include "Components/TextBlock.h"

AInfiniteDriverHUD::AInfiniteDriverHUD()
{
	/**  set the widget asset */
	static ConstructorHelpers::FClassFinder<UUserWidget> HUDWidgetClassBPClass(TEXT("/Game/MyBP/UI/WBP_InfiniteDriverWid"));
	if (HUDWidgetClassBPClass.Class)
	{
		HUDWidgetClass = HUDWidgetClassBPClass.Class;
	}
}

void AInfiniteDriverHUD::BeginPlay()
{
	Super::BeginPlay();

	/** set owner ref  */
	if (ATruck* TestTruck = Cast<ATruck>(GetOwningPawn()))
	{
		Truck = TestTruck;
	}

	CreateHUD();
}

void AInfiniteDriverHUD::DrawHUD()
{
	Super::DrawHUD();
	
	if (CurrentWidget && Truck)
	{
		/** set health  */
		if (CurrentWidget->HealthBar)
		{
			float Percent = Truck->GetHealth() / 100.f;
			CurrentWidget->HealthBar->SetPercent(Percent);
		}

		/** set coins  */
		if (CurrentWidget->Coins)
		{
			FString String = FString::Printf(TEXT("Coins : %d"), Truck->Coins);
			FText InText = FText::FromString(String);
			CurrentWidget->Coins->SetText(InText);
		}

		/** set distance  */
		if (CurrentWidget->Distance)
		{
			FString String = FString::Printf(TEXT("%d m"), (int32)Truck->Distance);
			FText InText = FText::FromString(String);
			CurrentWidget->Distance->SetText(InText);
		}
	}
}

void AInfiniteDriverHUD::CreateHUD() 
{
	if (HUDWidgetClass)
	{
		CurrentWidget = CreateWidget<UInfiniteDriverWidget>(GetWorld(), HUDWidgetClass);
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
	}
}
