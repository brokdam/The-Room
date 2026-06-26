#include "TheRoomCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "Item/BaseItem.h"
#include "Blueprint/UserWidget.h"
#include "Item/Desk.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ATheRoomCharacter::ATheRoomCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

}

//////////////////////////////////////////////////////////////////////////// Input

void ATheRoomCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ATheRoomCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATheRoomCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATheRoomCharacter::Look);
		
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ATheRoomCharacter::Interact);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void ATheRoomCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ATheRoomCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ATheRoomCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector Start = FirstPersonCameraComponent->GetComponentLocation();
	FVector End = Start + (FirstPersonCameraComponent->GetForwardVector() * 700.0f);

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	
	bool bHit = 
		GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, QueryParams);
	
	ABaseItem* HitItem = nullptr;
    
	if (bHit)
	{
		ADesk* HitDesk = Cast<ADesk>(HitResult.GetActor());
		
		if (HitDesk)
		{
			if (HitDesk->IsHitComponentDrawer(HitResult.GetComponent()))
			{
				HitItem = HitDesk;
			}
		}
		else
		{
			HitItem = Cast<ABaseItem>(HitResult.GetActor());
		}
	}
	
	if (HitItem != CurrentInteractable)
	{
		if (CurrentInteractable)
		{
			HideInteraction();
			if (UStaticMeshComponent* OutlineMesh = CurrentInteractable->GetOutlineMesh())
			{
				OutlineMesh->SetRenderCustomDepth(false);
			}
		}

		CurrentInteractable = HitItem;

		if (CurrentInteractable)
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit Item: %s"), *CurrentInteractable->GetName()); // 추가

			ShowInteraction();
			if (UStaticMeshComponent* OutlineMesh = CurrentInteractable->GetOutlineMesh())
			{
				OutlineMesh->SetRenderCustomDepth(true);
			}
		}
	}
}

void ATheRoomCharacter::Interact()
{
	if (CurrentInteractable)
	{
		CurrentInteractable->ActivateItem(this);
	}
}

void ATheRoomCharacter::ShowInteraction()
{
	if (!InteractionWidgetInstance && InteractionWidgetClass)
	{
		InteractionWidgetInstance = CreateWidget<UInteractionWidget>(GetWorld(), InteractionWidgetClass);
		InteractionWidgetInstance->AddToViewport();
	}
}

void ATheRoomCharacter::HideInteraction()
{
	if (InteractionWidgetInstance)
	{
		InteractionWidgetInstance->RemoveFromParent();
		InteractionWidgetInstance = nullptr;
	}
}
