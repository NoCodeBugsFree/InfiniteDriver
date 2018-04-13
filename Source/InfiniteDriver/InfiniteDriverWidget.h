// Only 3dMotive and Crocopede has permission to redistribuite this project and all of its contents.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InfiniteDriverWidget.generated.h"

/**
 * 
 */
UCLASS()
class INFINITEDRIVER_API UInfiniteDriverWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	/**  HealthBar reference  */
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;

	/**  Distance reference  */
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Distance;

	/**  Coins  reference  */
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Coins;

};
