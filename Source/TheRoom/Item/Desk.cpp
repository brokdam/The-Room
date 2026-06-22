#include "Item/Desk.h"

ADesk::ADesk()
{
	DeskMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DeskMesh"));
	DeskMesh->SetupAttachment(Scene);
    
	DrawerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DrawerMesh"));
	DrawerMesh->SetupAttachment(DeskMesh);
    
	ItemType = "Desk";
}

void ADesk::ActivateItem(AActor* Activator)
{
	if (Activator && Activator->ActorHasTag("Player"))
	{
		bIsOpen = !bIsOpen;
        
		if (bIsOpen)
		{
			DrawerOpen();
		}
		else
		{
			DrawerClose();
		}
	}
}
