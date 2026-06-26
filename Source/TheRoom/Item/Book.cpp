#include "Item/Book.h"
#include "Item/BrightLetter.h"

ABook::ABook()
{
	ItemType = "Book";
}

void ABook::ActivateItem(AActor* Activator)
{
	if (Activator && Activator->ActorHasTag("Player"))
	{
		bIsPulled = !bIsPulled; // 누를 때마다 상태 반전
		
		if (bIsPulled)
		{
			BookPull();
		}
		else
		{
			BookPush();
		}
	}
}

void ABook::PullFinished()
{
	if (HiddenNote)
	{
		HiddenNote->Reveal();
	}
}