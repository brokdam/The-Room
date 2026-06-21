#include "Item/Door.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Item/DarkLetter.h"
#include "UI/InteractionWidget.h"
#include "Blueprint/UserWidget.h"
#include "TheRoomCharacter.h"

ADoor::ADoor()
{
	Collision->SetBoxExtent(FVector(100.0f, 300.0f, 200.0f));
	ItemType = "Door";
}

void ADoor::ActivateItem(AActor* Activator)
{
	if (Activator && Activator->ActorHasTag("Player"))
	{
		ATheRoomCharacter* PlayerCharacter = Cast<ATheRoomCharacter>(Activator);
		if (!PlayerCharacter) return;
		
		if (RequiredLetter && !RequiredLetter->IsRead())
		{
			if (LockedWidgetInstance)
			{
				LockedWidgetInstance->RemoveFromParent();
				LockedWidgetInstance = nullptr;
				PlayerCharacter->ShowInteraction();
			}
			else if (LockedMessageClass)
			{
				LockedWidgetInstance = CreateWidget<UInteractionWidget>(GetWorld(), LockedMessageClass);
				LockedWidgetInstance->AddToViewport();
				PlayerCharacter->HideInteraction();
			}
		}
		else
		{
			UGameplayStatics::OpenLevel(this, FName("BrightRoom"));
		}
	}
}
