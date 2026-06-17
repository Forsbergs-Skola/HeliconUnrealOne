// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

struct FInputActionValue;
class UInputAction;

UCLASS()
class HELICONUNREAL_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Input")
	class UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Input")
	UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Input")
	TObjectPtr<UInputAction> CrouchAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Input")
	TObjectPtr<UInputAction> LookAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Input")
	TObjectPtr<UInputAction> InteractAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Movement")
	float WalkSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Movement")
	float CrouchSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Character")
	TObjectPtr<UStaticMeshComponent> MeshComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Character")
	TObjectPtr<class UCameraComponent> FirstPersonCamera;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Character")
	TObjectPtr<class USpringArmComponent> SpringArm;
	
	UPROPERTY(BlueprintReadWrite, Category="Interaction")
	AActor*CurrentInteractable;
	
protected:
	virtual void BeginPlay() override;

public:	
	void DoInteract();
	void SetCurrentInteractable(AActor* NewInteractable);
	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void OnMove(const FInputActionValue& Value);
	void OnCrouch(const FInputActionValue& Value);
	void OnLook(const FInputActionValue& Value);
};
