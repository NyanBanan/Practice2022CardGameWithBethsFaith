// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Card.h"
#include <Kismet/GameplayStatics.h>
#include "PlayerCardController.generated.h"
// авторство глупой девочки
/**
 * 
 */
UCLASS()
class PRACTICE2022_API APlayerCardController : public APlayerController
{
	GENERATED_BODY()

	virtual void SetupInputComponent() override;

	void OnMouseClick();

	void ZoomCard();

};
