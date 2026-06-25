#pragma once

#include "CoreMinimal.h"
#include "Item/BaseItem.h"
#include "BrightLetter.generated.h"

class ULetterWidget;

UCLASS()
class THEROOM_API ABrightLetter : public ABaseItem
{
	GENERATED_BODY()
	
public: 
	ABrightLetter();
	
	virtual void ActivateItem(AActor* Activator) override;
	
	void Reveal();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Letter")
	TSubclassOf<ULetterWidget> LetterWidgetClass;
	
	UPROPERTY(BlueprintReadOnly, Category = "Letter")
	bool bRevealed = false;
	
	UPROPERTY()
	ULetterWidget* LetterWidgetInstance;
};