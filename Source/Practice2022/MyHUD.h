// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"
#include "Engine/World.h"
#include "MyHUD.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FMessage
{
	GENERATED_BODY()

	UPROPERTY()
	UTexture2D* tex;
	UPROPERTY()
	FString message;
	UPROPERTY()
	float time;
	UPROPERTY()
	FColor color;

	FMessage()
	{
		tex = nullptr;
		message = " ";
		time = 5.f;
		color = FColor::White;
	}
	FMessage(UTexture2D* itex, FString iMessage, float iTime, FColor iColor)
	{
		tex = itex;
		message = iMessage;
		time = iTime;
		color = iColor;
	}
};

UCLASS()
class PRACTICE2022_API AMyHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUDFont)
	UFont* hudFont;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUDFont)
	TArray<FMessage> messages;

	virtual void DrawHUD() override;
	void addMessage(FMessage msg);
};
