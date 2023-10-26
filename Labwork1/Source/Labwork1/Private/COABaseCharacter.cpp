// Fill out your copyright notice in the Description page of Project Settings.


#include "COABaseCharacter.h"


// Sets default values
ACOABaseCharacter::ACOABaseCharacter() :

	bDead(false),
	Health(100.0f),
	MaxHealth(100.0f),
	HealingRate(0.0f),
	WalkSpeed(600.0f),
	RunSpeed(1200.0f)

{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
}

// Called when the game starts or when spawned
void ACOABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACOABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACOABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

