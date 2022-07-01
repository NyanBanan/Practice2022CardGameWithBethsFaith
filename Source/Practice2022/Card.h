// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <Runtime/Engine/Classes/Components/TextRenderComponent.h>
#include "Card.generated.h"


UCLASS()
class PRACTICE2022_API ACard : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACard(); /*: ACard(FString(" "), 99, 99, FText::FromString(FString("Name"))){}*/
	//ACard(FString PictureTex, int32 HP_, int32 Damage_, FText Name_);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Card_Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Picture_Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UTextRenderComponent* Text_HP;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) 
	UTextRenderComponent* Text_Damage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UTextRenderComponent* Text_Name;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UTextRenderComponent* Text_Effect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int HP = 99;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Damage = 99;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name = FText::FromString("TEST");
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Effect = FText::FromString("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsZoomed = false;

	UFUNCTION(BlueprintCallable)
	void VisualStats();

	UFUNCTION(BlueprintCallable)
	void SetLastLocation(FVector loc);

	UFUNCTION(BlueprintCallable)
	FVector GetLastLocation();
	FRotator GetLastRotation();

	UFUNCTION(BlueprintImplementableEvent)
	void BattleCry();

	// авторство глупой девочки
	void MoveAndRotate(float x, float y, float z, double pitch, double yaw, double roll);
	UFUNCTION(BlueprintCallable)
	bool isDead();
	UFUNCTION(BlueprintCallable)
	void Attack(ACard* DamageRecipient);
	void SetProperties(int HP_, int Damage_, FText Name_, FText Effect_);

	friend void AttackEachOther(ACard* Card1, ACard* Card2);
private:
	//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector MyLastLocation;
	FRotator MyLastRotation;
};

