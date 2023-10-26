// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "COABaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "COAAvatar.generated.h"


/**
 * 
 */
UCLASS()
class LABWORK1_API ACOAAvatar : public ACOABaseCharacter
{
	GENERATED_BODY()


public:
	ACOAAvatar();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "COA")
	 UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "COA")
	 USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "COA")
	 float StaminaDrainRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "COA")
	 float StaminaGainRate;

	UPROPERTY(EditAnywhere, Category = "COA")
	 float MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "COA")
	 float Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "COA")
	 bool bStaminaDrained;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "COA")
	 bool bRunning;

	 virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	
	void MoveForward(float value);
	void TurnRight(float value);
	void RunPressed();
	void RunReleased();
	void UpdateMovementParameters();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
