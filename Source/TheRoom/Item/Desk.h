#pragma once

#include "CoreMinimal.h"
#include "Item/BaseItem.h"
#include "Desk.generated.h"

UCLASS()
class THEROOM_API ADesk : public ABaseItem
{
	GENERATED_BODY()
	
public:
	ADesk();
	
	virtual void ActivateItem(AActor* Activator) override;
	
	bool IsHitComponentDrawer(UPrimitiveComponent* HitComponent) const;
	
	virtual UStaticMeshComponent* GetOutlineMesh() const override { return DrawerMesh; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Desk")
	UStaticMeshComponent* DeskMesh;
    
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Desk")
	UStaticMeshComponent* DrawerMesh;
    
	UPROPERTY(BlueprintReadOnly, Category = "Desk")
	bool bIsOpen = false;
    
	UFUNCTION(BlueprintImplementableEvent, Category = "Desk")
	void DrawerOpen();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Desk")
	void DrawerClose();
};
