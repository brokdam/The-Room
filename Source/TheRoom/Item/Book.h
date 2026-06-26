#pragma once

#include "CoreMinimal.h"
#include "Item/BaseItem.h"
#include "Book.generated.h"

class ABrightLetter;

UCLASS()
class THEROOM_API ABook : public ABaseItem
{
	GENERATED_BODY()
	
public:
	ABook();
	virtual void ActivateItem(AActor* Activator) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Book")
	ABrightLetter* HiddenNote;
	
	UPROPERTY(BlueprintReadOnly, Category = "Book")
	bool bIsPulled = false;
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Book")
	void BookPull(); // C++엔 구현 없음, 블루프린트 Timeline이 채움
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Book")
	void BookPush();
	
	UFUNCTION(BlueprintCallable, Category = "Book")
	void PullFinished(); // Timeline의 Finished 핀에서 호출
	
};