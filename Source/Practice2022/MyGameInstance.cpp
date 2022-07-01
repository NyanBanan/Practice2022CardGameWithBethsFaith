// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "MyHUD.h"

void UMyGameInstance::OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld)
{
	if (NewWorld == nullptr)
		return;

	if (NewWorld->GetName() == "1")
		LevelNumber = 0;

	if (NewWorld->GetName() == "CardGameFire")
		LevelNumber = 1;

	if (NewWorld->GetName() == "CardGame_Budda")
		LevelNumber = 2;

	if (NewWorld->GetName() == "CardGameCastle")
		LevelNumber = 3;
}
