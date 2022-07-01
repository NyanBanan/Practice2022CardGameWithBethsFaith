// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Card.h"
#include "CardPlace.generated.h"

// авторство глупой девочки

UCLASS()
class PRACTICE2022_API ACardPlace : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACardPlace();
	ACardPlace(UStaticMeshComponent* iVMCube, UStaticMeshComponent* iVMFCube, ACard* iCard);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* InvisibleMeshCube;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* VisualMeshCubeFrame;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FrameCube)
	TArray<UStaticMeshComponent*> FrameCubes;

	UFUNCTION(BlueprintCallable)
	ACard* GetCard();
	UFUNCTION(BlueprintCallable)
	ACard* PickUp();              // отдать карту (освободить место)
	bool IsEmptyPlace();          // проверка на пустое место

	void SetCard(ACard* iCard);
	void SetAndMoveCard(ACard* iCard);
	void SetAndMoveCardInHand(ACard* iCard);

	void SetLocation(FVector loc);
	void SetLocationAndRotation(FVector loc, FRotator rot);

	UFUNCTION(BlueprintCallable)
	void DestroyCard();			  // уничтожить карту и освободить место
	UFUNCTION(BlueprintCallable)
	void ToFree();                // освободить место под карту

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsPlayersPlace = false; // карта в руке игрока?

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsPlayersHand = false;  // карта в руке противника?
private:
	ACard* Card;
};
