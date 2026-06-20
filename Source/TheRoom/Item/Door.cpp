#include "Item/Door.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

ADoor::ADoor()
{
	Collision->SetBoxExtent(FVector(100.0f, 300.0f, 200.0f));
	ItemType = "Door";
}

void ADoor::ActivateItem(AActor* Activator)
{
	if (Activator && Activator->ActorHasTag("Player"))
	{
		UGameplayStatics::OpenLevel(this, FName("BrightRoom"));
	}
}
