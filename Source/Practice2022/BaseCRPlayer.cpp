// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCRPlayer.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
ABaseCRPlayer::ABaseCRPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Speed = 500;
	GetCharacterMovement()->MaxWalkSpeed = Speed;
	jumping = false;
	running = false;
}

// Called when the game starts or when spawned
void ABaseCRPlayer::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseCRPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (jumping)
		Jump();
}

// Called to bind functionality to input
void ABaseCRPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABaseCRPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseCRPlayer::MoveRight);

	// Set up "look" bindings.
	PlayerInputComponent->BindAxis("Turn", this, &ABaseCRPlayer::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ABaseCRPlayer::AddControllerPitchInput);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ABaseCRPlayer::CheckJumping);
	InputComponent->BindAction("Jump", IE_Released, this, &ABaseCRPlayer::CheckJumping);

	InputComponent->BindAction("ToggleRun", IE_Pressed, this, &ABaseCRPlayer::CheckRunning);

	InputComponent->BindAction("Sprint", IE_Pressed, this, &ABaseCRPlayer::CheckRunning);
	InputComponent->BindAction("Sprint", IE_Released, this, &ABaseCRPlayer::CheckRunning);
}

void ABaseCRPlayer::MoveForward(float Value)
{
	// Find out which way is "forward" and record that the player wants to move that way.
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void ABaseCRPlayer::MoveRight(float Value)
{
	// Find out which way is "right" and record that the player wants to move that way.
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void ABaseCRPlayer::CheckJumping()
{
	if (jumping)
		jumping = false;
	else
		jumping = true;
}

void ABaseCRPlayer::CheckRunning()
{
	if (running)
	{
		running = false;
		GetCharacterMovement()->MaxWalkSpeed = 1 * Speed;
	}
	else
	{
		running = true;
		GetCharacterMovement()->MaxWalkSpeed = 2 * Speed;
	}
}

