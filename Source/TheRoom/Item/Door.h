#pragma once

#include "CoreMinimal.h"
#include "Item/BaseItem.h"
#include "Door.generated.h"

UCLASS()
class THEROOM_API ADoor : public ABaseItem
{
	GENERATED_BODY()
	
public:
	ADoor();
	
	virtual void ActivateItem(AActor* Activator) override;
};
