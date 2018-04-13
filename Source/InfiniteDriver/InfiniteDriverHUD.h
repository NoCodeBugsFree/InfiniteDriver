// Only 3dMotive and Crocopede has permission to redistribuite this project and all of its contents.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "InfiniteDriverHUD.generated.h"

/**
 * 
 */
UCLASS()
class INFINITEDRIVER_API AInfiniteDriverHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	AInfiniteDriverHUD();

	virtual void BeginPlay() override;

	virtual void DrawHUD() override;
	
private:

	/** called to  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void CreateHUD();

	/** widget class */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	/** current active widget */
	UPROPERTY()
	class UInfiniteDriverWidget* CurrentWidget;

	/** Owner reference  */
	UPROPERTY(BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	class ATruck* Truck;
};
