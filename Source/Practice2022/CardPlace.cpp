// Fill out your copyright notice in the Description page of Project Settings.
#include "CardPlace.h"
#include "Deck.h"


// авторство глупой девочки

// Sets default values
ACardPlace::ACardPlace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InvisibleMeshCube = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	InvisibleMeshCube->SetupAttachment(RootComponent);

	VisualMeshCubeFrame = CreateDefaultSubobject<UStaticMeshComponent>("Mesh2");

	for (int i = 0; i < 4; ++i)
	{
		UStaticMeshComponent* newStatMesh = CreateDefaultSubobject<UStaticMeshComponent>("Meshuares" + i);
		FrameCubes.Add(newStatMesh);
		FrameCubes[i]->SetupAttachment(VisualMeshCubeFrame);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Engine/BasicShapes/Cube"));
	if (CubeVisualAsset.Succeeded())
	{
		InvisibleMeshCube->SetStaticMesh(CubeVisualAsset.Object);
		for (int i{}; i < 4; ++i)
			FrameCubes[i]->SetStaticMesh(CubeVisualAsset.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> FrameMaterial(TEXT("/Game/Materials/red"));
	if (FrameMaterial.Succeeded())
		for (int i{}; i < 4; ++i)
			FrameCubes[i]->SetMaterial(0, FrameMaterial.Object);


	InvisibleMeshCube->SetRelativeScale3D(FVector(12.0f, 12.0f, 0.25f));
	InvisibleMeshCube->SetVisibility(false);


	for (int i{}; i < 2; ++i)
	{
		FrameCubes[i]->SetRelativeScale3D(FVector(11.6f, 0.25f, 0.25f));
		FrameCubes[i]->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		//FrameCubes[i]->SetVisibility(true);
	}
	for (int i{ 2 }; i < 4; ++i)
	{
		FrameCubes[i]->SetRelativeScale3D(FVector(12.03f, 0.25f, 0.25f));
		FrameCubes[i]->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
		//FrameCubes[i]->SetVisibility(true);
	}

	FrameCubes[0]->SetRelativeLocation(FVector(0.0f, 600.0f, 0.0f));
	FrameCubes[1]->SetRelativeLocation(FVector(0.0f, -610.0f, 0.0f));
	FrameCubes[2]->SetRelativeLocation(FVector(570.0f, 0.0f, 0.0f));
	FrameCubes[3]->SetRelativeLocation(FVector(-570.0f, 0.0f, 0.0f));

	Card = nullptr;
}

ACardPlace::ACardPlace(UStaticMeshComponent* iVMCube, UStaticMeshComponent* iVMFCube, ACard* iCard)
{
	PrimaryActorTick.bCanEverTick = true;
	InvisibleMeshCube = iVMCube;
	VisualMeshCubeFrame = iVMFCube;
	Card = iCard;
}

// Called when the game starts or when spawned
void ACardPlace::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACardPlace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


ACard* ACardPlace::GetCard()
{
	return Card;
}

ACard* ACardPlace::PickUp()
{
	ACard* ret = Card;
	Card = nullptr;
	return ret;
}

bool ACardPlace::IsEmptyPlace()
{
	return Card == nullptr;
}

void ACardPlace::SetCard(ACard* iCard)
{
	Card = iCard;
}

void ACardPlace::SetAndMoveCard(ACard* iCard)
{
	if (iCard == nullptr) return;
	Card = iCard;
	FVector loc = this->GetActorLocation();
	FRotator rot = this->GetActorRotation();

	Card->MoveAndRotate(loc.X, loc.Y+25, loc.Z, rot.Pitch, rot.Yaw + 90, rot.Roll);
}

void ACardPlace::SetAndMoveCardInHand(ACard* iCard)
{
	if (iCard == nullptr) return;
	Card = iCard;
	FVector loc = this->GetActorLocation();
	FRotator rot = this->GetActorRotation();

	if (bIsPlayersHand)
		Card->MoveAndRotate(loc.X, loc.Y + 25, loc.Z, 0, 90, 60);
	else
		Card->MoveAndRotate(loc.X, loc.Y + 25, loc.Z, 0, -90, 60);
}

void ACardPlace::SetLocation(FVector loc)
{
	InvisibleMeshCube->SetWorldLocation(loc);
	VisualMeshCubeFrame->SetWorldLocation(loc);
}

void ACardPlace::SetLocationAndRotation(FVector loc, FRotator rot)
{
	InvisibleMeshCube->SetWorldLocation(loc);
	VisualMeshCubeFrame->SetWorldLocation(loc);
	InvisibleMeshCube->SetWorldRotation(rot);
	VisualMeshCubeFrame->SetWorldRotation(rot);
}

void ACardPlace::DestroyCard()
{
	Card->Destroy();
	Card = nullptr;
}

void ACardPlace::ToFree()
{
	Card = nullptr;
}