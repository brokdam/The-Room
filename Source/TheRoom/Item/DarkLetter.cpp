#include "Item/DarkLetter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

ADarkLetter::ADarkLetter()
{
	Collision->SetBoxExtent(FVector(200.0f, 200.0f, 200.0f));
	ItemType = "DarkLetter";
}

void ADarkLetter::ActivateItem(AActor* Activator)
{
	TArray<AActor*> OverlappingActors;
	Collision->GetOverlappingActors(OverlappingActors);
	
	for (AActor* Actor : OverlappingActors)
	{
		if (Activator && Activator->ActorHasTag("Player"))
		{
			
		}
	}
}
