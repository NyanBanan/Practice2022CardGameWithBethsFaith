// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "NPC.generated.h"

UCLASS()
class PRACTICE2022_API ANPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
	USphereComponent* ProxSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NPCMessage)
	FString NPCMessage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NPCMessage)
	float NPCTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NPCMessage)
	FColor NPCColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NPCName)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NPCMessage)
	UTexture2D* Face;

	UFUNCTION(BlueprintNativeEvent, Category = "Collision")
	void Prox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
