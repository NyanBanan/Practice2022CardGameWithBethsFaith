// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayer.h"

// Sets default values
ABasePlayer::ABasePlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SceletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SceletalMesh");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	//RootComponent = Mesh;
	RootComponent = SceletalMesh;
	SpringArm->SetupAttachment(SceletalMesh);
	Camera->SetupAttachment(SpringArm);

	//Mesh->SetSimulatePhysics(true);
	MovementForce = 10000;
	JumpImpulse = 1000;
	jumping = false;
}

// Called when the game starts or when spawned
void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (jumping)
		Jump();
}

// Called to bind functionality to input
void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &ABasePlayer::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ABasePlayer::MoveRight);

	//InputComponent->BindAction("Jump", IE_Pressed, this, &ABasePlayer::Jump);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ABasePlayer::CheckJumping);
	InputComponent->BindAction("Jump", IE_Released, this, &ABasePlayer::CheckJumping);
}

void ABasePlayer::MoveForward(float value)
{
	FVector ForceToAdd{ FVector(1,0,0) * value * MovementForce };
	SceletalMesh->AddForce(ForceToAdd);
}

void ABasePlayer::MoveRight(float value)
{
	FVector ForceToAdd{ FVector(0,1,0) * value * MovementForce };
	SceletalMesh->AddForce(ForceToAdd);
}

void ABasePlayer::CheckJumping()
{
	if (jumping)
		jumping = false;
	else
		jumping = true;
}
