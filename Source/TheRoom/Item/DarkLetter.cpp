#include "Item/DarkLetter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/LetterWidget.h"
#include "Blueprint/UserWidget.h"
#include "TheRoomCharacter.h"

ADarkLetter::ADarkLetter()
{
	Collision->SetBoxExtent(FVector(200.0f, 200.0f, 200.0f));
	ItemType = "DarkLetter";
}

void ADarkLetter::ActivateItem(AActor* Activator)
{
	if (Activator && Activator->ActorHasTag("Player"))
	{
		ATheRoomCharacter* PlayerCharacter = Cast<ATheRoomCharacter>(Activator);
		if (!PlayerCharacter) return;
		
		if (LetterWidgetInstance)
		{
			LetterWidgetInstance->RemoveFromParent();
			LetterWidgetInstance = nullptr;
			PlayerCharacter->ShowInteraction();
		}
		else if (LetterWidgetClass)
		{
			LetterWidgetInstance = CreateWidget<ULetterWidget>(GetWorld(), LetterWidgetClass);
			LetterWidgetInstance->AddToViewport();
			PlayerCharacter->HideInteraction();
			bRead = true;
		}
	}
}

bool ADarkLetter::IsRead() const
{
	return bRead;
}
