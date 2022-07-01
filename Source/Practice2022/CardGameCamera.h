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

	//������ �� ������ ������� ����� ��������� 1 ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* CameraOne;
	//������ �� ������ ������� ����� ��������� 2 ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* CameraTwo;
	//������ �� ������ ������� ����� ��������� 3 ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* CameraThree;

	UFUNCTION(BlueprintCallable)
	void NextCamera();
	UFUNCTION(BlueprintCallable)
	void PrevCamera();

	// ��������� ������ �������

	const int& GetCameraNumber();
	ACard* GetSelectedCard();
	void SetSelectedCard(ACard* InputCard);

	ACard* GetZoomedCard();
	void SetZoomedCard(ACard* InputCard);

private:
	int CameraNumber = 0;

	ACard* SelectedCard = nullptr;         // ��������� �����
	ACard* ZoomedCard = nullptr;
};
