// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraActor.h"
#include "GameFramework/Pawn.h"
#include "Card.h"
#include "CardPlace.h"
#include "CardGameCamera.generated.h"

UCLASS()
class PRACTICE2022_API ACardGameCamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACardGameCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//ссылка на актера которым будем управлять 1 камера
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* CameraOne;
	//ссылка на актера которым будем управлять 2 камера
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* CameraTwo;
	//ссылка на актера которым будем управлять 3 камера
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* CameraThree;

	UFUNCTION(BlueprintCallable)
	void NextCamera();
	UFUNCTION(BlueprintCallable)
	void PrevCamera();

	// авторство глупой девочки

	const int& GetCameraNumber();
	ACard* GetSelectedCard();
	void SetSelectedCard(ACard* InputCard);

	ACard* GetZoomedCard();
	void SetZoomedCard(ACard* InputCard);

private:
	int CameraNumber = 0;

	ACard* SelectedCard = nullptr;         // выбранная карта
	ACard* ZoomedCard = nullptr;
};
