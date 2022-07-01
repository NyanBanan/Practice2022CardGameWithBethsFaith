// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"
/**
 * 
 */
UCLASS()
class PRACTICE2022_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int LevelNumber;

	UFUNCTION()
	virtual void OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld) override;
};
