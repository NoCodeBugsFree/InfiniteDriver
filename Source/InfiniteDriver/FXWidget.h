// Only 3dMotive and Crocopede has permission to redistribuite this project and all of its contents.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FXWidget.generated.h"

/**
 * TODO event construct -> set alignment in viewport (0.5 0.5) --- delay 0.3 --- remove from parent 
 */
UCLASS()
class INFINITEDRIVER_API UFXWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	/**  Message reference  */
	UPROPERTY(meta = (BindWidget), VisibleAnywhere, BlueprintReadWrite)
	class UTextBlock* Message;
	
};
