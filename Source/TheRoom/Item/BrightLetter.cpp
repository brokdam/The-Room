#include "Item/BrightLetter.h"
#include "UI/LetterWidget.h"
#include "Blueprint/UserWidget.h"
#include "TheRoomCharacter.h"

ABrightLetter::ABrightLetter()
{
	ItemType = "BrightLetter";
	
	// StaticMesh->SetVisibility(false);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABrightLetter::ActivateItem(AActor* Activator)
{
	if (!bRevealed) return;
	
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
		}
	}
}

void ABrightLetter::Reveal()
{
	if (bRevealed) return;
	
	bRevealed = true;
	
	StaticMesh->SetVisibility(true);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	
	StaticMesh->SetEnableGravity(true);
	StaticMesh->SetSimulatePhysics(true);
}