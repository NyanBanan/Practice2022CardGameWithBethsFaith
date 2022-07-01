// Fill out your copyright notice in the Description page of Project Settings.


#include "Card.h"
//#include "D:\Diff Folders From C\Workbench\Code\UnrealProjects\Practice2022\Content\Blueprints\BP_Card.uasset"
// Sets default values
ACard::ACard() 
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Card_Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Card_Mesh");
	Picture_Mesh= CreateDefaultSubobject<UStaticMeshComponent>("Picture_Mesh");
	Text_HP = CreateDefaultSubobject<UTextRenderComponent>("Text_HP");
	Text_Damage = CreateDefaultSubobject<UTextRenderComponent>("Text_Damage");
	Text_Name = CreateDefaultSubobject<UTextRenderComponent>("Text_Name");
	Text_Effect = CreateDefaultSubobject<UTextRenderComponent>("Text_Efect");


	RootComponent = Card_Mesh;
	Picture_Mesh->SetupAttachment(Card_Mesh);

	Text_HP->SetupAttachment(Card_Mesh);
	Text_Damage->SetupAttachment(Card_Mesh);
	Text_Name->SetupAttachment(Card_Mesh);
	Text_Effect->SetupAttachment(Card_Mesh);

	Picture_Mesh->SetWorldLocation(FVector(-40,-90,40));
	Picture_Mesh->SetWorldScale3D(FVector(0.25,0.25,0.01));
	Text_HP->SetWorldLocationAndRotation(FVector(260, 530, 90),FRotator(90,180,90));
	Text_Damage->SetWorldLocationAndRotation(FVector(-500, 530, 90), FRotator(90, 180, 90));
	Text_Name->SetWorldLocationAndRotation(FVector(-165, -348, 70), FRotator(90, 180, 90));

	Text_HP->WorldSize=150;
	Text_HP->SetTextRenderColor(FColor(0,255, 60, 255));
	Text_Damage->WorldSize = 150;
	Text_Damage->SetTextRenderColor(FColor(255, 0, 0,255));
	Text_Name->WorldSize = 100;

	Text_Effect->WorldSize = 80;
	Text_Effect->SetWorldLocationAndRotation(FVector(-30, 340, 90), FRotator(90, -90, 180));
	Text_Effect->SetHorizontalAlignment(EHTA_Center);
	Text_Effect->SetTextRenderColor(FColor(0, 0, 0, 0));
}


 //Called when the game starts or when spawned
void ACard::BeginPlay()
{
	Super::BeginPlay();
	MyLastLocation = this->GetActorLocation();
}

// Called every frame
//void ACard::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

// Called to bind functionality to input
//void ACard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//}

void ACard::VisualStats() {
	Text_HP->SetText(FText::AsNumber(HP));
	Text_Damage->SetText(FText::AsNumber(Damage));
	Text_Name->SetText(Name);
	Text_Effect->SetText(Effect);
}


void ACard::SetLastLocation(FVector loc)
{
	this->MyLastLocation = loc;
}

FVector ACard::GetLastLocation() {
	return this->MyLastLocation;
}

FRotator ACard::GetLastRotation()
{
	return this->MyLastRotation;
}

// авторство умной девочки
void ACard::MoveAndRotate(float x, float y, float z, double pitch, double yaw, double roll)
{
	MyLastLocation = this->GetActorLocation();
	MyLastRotation = this->GetActorRotation();
	this->SetActorLocationAndRotation(FVector(x, y, z), FRotator(pitch, yaw, roll));
}

bool ACard::isDead()
{
	return this->HP <= 0;
}

void ACard::Attack(ACard* DamageRecipient)
{
	DamageRecipient->HP -= this->Damage;
	DamageRecipient->VisualStats();
}

void ACard::SetProperties(int HP_, int Damage_, FText Name_, FText Effect_)
{
	HP = HP_;
	Damage = Damage_;
	Name = Name_;
	Effect = Effect_;
}

void AttackEachOther(ACard* Card1, ACard* Card2)
{
	Card1->Attack(Card2);
	Card2->Attack(Card1);
}
