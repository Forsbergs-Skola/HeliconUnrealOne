// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "BaseWeatherManipulator.h"
#include "InputPriority.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TestAddProgressionAmount = 1;

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	WeatherManipulator = Cast<ABaseWeatherManipulator>(UGameplayStatics::GetActorOfClass(GetWorld(), ABaseWeatherManipulator::StaticClass()));

	if (APlayerController* PC = Cast<APlayerController>(GetController())) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer())) {
			if (MappingContext) {
				Subsystem->AddMappingContext(MappingContext, 0);
			}
		}
	}
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller == nullptr) return;

	const FRotator Rotation = Controller->GetControlRotation();

	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

void ABaseCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxis = Value.Get<FVector2D>();

	if (Controller == nullptr) return;

	
	AddControllerYawInput(LookAxis.X);
	AddControllerPitchInput(LookAxis.Y);
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (!EnhancedInput) return;

	if (MoveAction)
	{
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Move);
	}

	if (LookAction)
	{
		EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Look);
	}

	if (TestProgressionAction)
	{
		EnhancedInput->BindAction(
			TestProgressionAction,
			ETriggerEvent::Triggered,
			this,
			&ABaseCharacter::OnTestAddWeatherProgression
		);
	}

}

void ABaseCharacter::OnTestAddWeatherProgression() {
	if (WeatherManipulator)
	{
		WeatherManipulator->TestAddWeatherProgression();
	}
}
