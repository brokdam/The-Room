#pragma once

#include "CoreMinimal.h"
#include "Item/BaseItem.h"
#include "Door.generated.h"

class ADarkLetter;
class UInteractionWidget;

UCLASS()
class THEROOM_API ADoor : public ABaseItem
{
	GENERATED_BODY()
	
public:
	ADoor();
	
	virtual void ActivateItem(AActor* Activator) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door")
	ADarkLetter* RequiredLetter;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door")
	TSubclassOf<UInteractionWidget> LockedMessageClass;
	
	UPROPERTY()
	UInteractionWidget* LockedWidgetInstance;
};
