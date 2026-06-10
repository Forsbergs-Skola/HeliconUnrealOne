#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "BaseCharacter.generated.h"

UCLASS()
class HELICONUNREAL_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();

	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	void OnTestAddWeatherProgression();

protected:
	virtual void BeginPlay() override;

public:
	// Forward Declerations

	// input mapping context and the actions, create them in the editor and assign in the Character blueprint
	// Under details -> Input -> .. 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|General")
	TObjectPtr<class UInputMappingContext> MappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Enhanced Input Actions")
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Enhanced Input Actions")
	TObjectPtr<class UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Enhanced Input Actions")
	TObjectPtr<class UInputAction> TestProgressionAction;

	class ABaseWeatherManipulator* WeatherManipulator;

	// Properties 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
	int32 TestAddProgressionAmount; 
};
