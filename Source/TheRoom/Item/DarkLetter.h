#pragma once

#include "CoreMinimal.h"
#include "Item/BaseItem.h"
#include "DarkLetter.generated.h"

class ULetterWidget;

UCLASS()
class THEROOM_API ADarkLetter : public ABaseItem
{
	GENERATED_BODY()
	
public: 
	ADarkLetter();
	
	virtual void ActivateItem(AActor* Activator) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Letter")
	TSubclassOf<ULetterWidget> LetterWidgetClass;

	UPROPERTY()
	ULetterWidget* LetterWidgetInstance;
};
