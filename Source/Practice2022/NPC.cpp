// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"
#include "MyHUD.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "BaseCRPlayer.h"

// Sets default values
ANPC::ANPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProxSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Proximity Sphere"));
	ProxSphere->SetupAttachment(RootComponent);
	ProxSphere->SetSphereRadius(400.f);

	ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &ANPC::Prox);
	NPCMessage = "Hi";// сообщение по умолчанию, может быть отредактировано
	NPCTime = 5.f;
	NPCColor = FColor::White;
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANPC::Prox_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*
	OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult&
	SweepResult)
{
	// если актор, с которым произошло пересечение, это не игрок,
	// вы просто должны вернуться из функции
	if (Cast<ABaseCRPlayer>(OtherActor) == nullptr)
		return;

	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	if (PController)
	{
		AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());
		if (hud != nullptr)
			hud->addMessage(FMessage(Face, Name + FString(": ") + NPCMessage, NPCTime, NPCColor));
	}
}
