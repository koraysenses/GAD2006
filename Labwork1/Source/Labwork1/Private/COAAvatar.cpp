// Fill out your copyright notice in the Description page of Project Settings.


#include "COAAvatar.h"
#include "GameFramework/CharacterMovementComponent.h"


ACOAAvatar::ACOAAvatar() :
	MaxStamina(100.0f),
	bRunning(false),
	StaminaDrainRate(10.0f),
	StaminaGainRate(15.0f),
	Stamina(100.0f),
	bStaminaDrained(false)


{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->TargetArmLength = 300.0f;
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	
}


void ACOAAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &ACharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ACharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACOAAvatar::MoveForward);
	PlayerInputComponent->BindAxis("TurnRight", this, &ACOAAvatar::TurnRight);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ACOAAvatar::RunPressed);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ACOAAvatar::RunReleased);

}

void ACOAAvatar::MoveForward(float value)
{
	FRotator Rotation = GetController()->GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, value);

}

void ACOAAvatar::TurnRight(float value)
{
	FRotator Rotation = GetController()->GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection, value);

}

void ACOAAvatar::RunPressed()
{
	
	bRunning = true;
}

void ACOAAvatar::RunReleased()
{
	bRunning = false;
	
}


void ACOAAvatar::UpdateMovementParameters()
{
	GetCharacterMovement()->MaxWalkSpeed =
		bRunning && !bStaminaDrained ? RunSpeed : WalkSpeed;

}


void ACOAAvatar::BeginPlay()
{
	Super::BeginPlay();
}

void ACOAAvatar::Tick(float DeltaTime)
{

	UpdateMovementParameters();

	if (GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Walking)
	{
		if (bRunning && !bStaminaDrained)
		{
			if (!GetCharacterMovement()->Velocity.IsNearlyZero(0.01))
			{
				Stamina = FMath::Max(0.0f, Stamina - StaminaDrainRate * DeltaTime);
				if (Stamina == 0.0f)
				{
					bStaminaDrained = true;
					
				}
			}
		}
		else
		{
			{
				Stamina = FMath::Min(MaxStamina, Stamina + StaminaGainRate * DeltaTime);
				if (Stamina >= MaxStamina)
				{
					bStaminaDrained = false;
					
				}
			}
		}
	}
	GEngine->AddOnScreenDebugMessage(0, DeltaTime, FColor::Yellow, FString::Printf(TEXT("Stamina %f"), Stamina));
}


