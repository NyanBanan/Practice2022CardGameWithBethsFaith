// Fill out your copyright notice in the Description page of Project Settings.


#include "CardGameMode.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <dos.h>
#include "UObject/Object.h"
#include "MyGameInstance.h"

// by глупая девочка

ACardGameMode::ACardGameMode()
{
	PlayerHPPlace = nullptr;
	EnemyHPPlace = nullptr;
}

void ACardGameMode::BeginPlay()
{
	// карты здоровья (игрок/соперник)
	PlayerHPPlace = GetWorld()->SpawnActor<ACardPlace>(FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));
	EnemyHPPlace = GetWorld()->SpawnActor<ACardPlace>(FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));

	PlayerHPPlace->SetLocation(FVector(780.0f, 1700.0f, 100.0f));
	EnemyHPPlace->SetLocation(FVector(4630.0f, 1700.0f, 100.0f));

	// делаем границы невидимыми
	for (int i{}; i < 4; ++i)
	{
		PlayerHPPlace->FrameCubes[i]->SetVisibility(false);
		EnemyHPPlace->FrameCubes[i]->SetVisibility(false);
	}

	// Создаём карты для героя/врага
	ACard* Card1 = GetWorld()->SpawnActor<ACard>(FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));
	ACard* Card2 = GetWorld()->SpawnActor<ACard>(FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));

	Card1->SetProperties(50, 0, FText::FromString("Player"), FText::FromString(" "));

	if (Cast<UMyGameInstance>(GetGameInstance())!= nullptr)
	switch (Cast<UMyGameInstance>(GetGameInstance())->LevelNumber)
	{
	case 1:
		Card2->SetProperties(70, 0, FText::FromString("Fire"), FText::FromString(" "));
		break;
	case 2:
		Card2->SetProperties(75, 0, FText::FromString("GoldDog"), FText::FromString(" "));
		break;
	case 3:
		Card2->SetProperties(80, 0, FText::FromString("Knight"), FText::FromString(" "));
		break;
	default:
		break;
	}

	Card1->VisualStats();
	Card2->VisualStats();

	PlayerHPPlace->SetAndMoveCard(Card1);
	EnemyHPPlace->SetAndMoveCard(Card2);

	// карты на столе 
	for (int i = 0; i < 3; ++i) {
		PlayerPlacedCards.Add(GetWorld()->SpawnActor<ACardPlace>(FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f)));
		EnemyPlacedCards.Add(GetWorld()->SpawnActor<ACardPlace>(FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f)));
		PlayerPlacedCards[i]->bIsPlayersPlace = true;
	}
	PlayerPlacedCards[0]->SetLocation(FVector(2020.0f, 480.0f, 100.0f));
	PlayerPlacedCards[1]->SetLocation(FVector(2020.0f, 1720.0f, 100.0f));
	PlayerPlacedCards[2]->SetLocation(FVector(2020.0f, 2930.0f, 100.0f));

	EnemyPlacedCards[0]->SetLocation(FVector(3330.0f, 480.0f, 100.0f));
	EnemyPlacedCards[1]->SetLocation(FVector(3330.0f, 1720.0f, 100.0f));
	EnemyPlacedCards[2]->SetLocation(FVector(3330.0f, 2930.0f, 100.0f));
	// карты в руке

	for (int i = 0; i < 4; ++i) {
		EnemyHandCards.Add(GetWorld()->SpawnActor<ACardPlace>(FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f)));
		PlayerHandCards.Add(GetWorld()->SpawnActor<ACardPlace>(FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f)));
		PlayerHandCards[i]->bIsPlayersHand = true;
	}
	PlayerHandCards[0]->SetLocationAndRotation(FVector(-550.0f, 140.0f, 770.0f), FRotator(60.0f, 0.0f, 0.0f));
	PlayerHandCards[1]->SetLocationAndRotation(FVector(-550.0f, 1330.0f, 770.0f), FRotator(60.0f, 0.0f, 0.0f));
	PlayerHandCards[2]->SetLocationAndRotation(FVector(-550.0f, 2530.0f, 770.0f), FRotator(60.0f, 0.0f, 0.0f));
	PlayerHandCards[3]->SetLocationAndRotation(FVector(-550.0f, 3730.0f, 770.0f), FRotator(60.0f, 0.0f, 0.0f));

	EnemyHandCards[0]->SetLocationAndRotation(FVector(6010.0f, 3450.0f, 770.0f), FRotator(-60.0f, 0.0f, 0.0f));
	EnemyHandCards[1]->SetLocationAndRotation(FVector(6010.0f, 2250.0f, 770.0f), FRotator(-60.0f, 0.0f, 0.0f));
	EnemyHandCards[2]->SetLocationAndRotation(FVector(6010.0f, 1050.0f, 770.0f), FRotator(-60.0f, 0.0f, 0.0f));
	EnemyHandCards[3]->SetLocationAndRotation(FVector(6010.0f, -140.0f, 770.0f), FRotator(-60.0f, 0.0f, 0.0f));

	srand(static_cast<unsigned int>(time(0))); // устанавливаем значение системных часов в качестве стартового числа
	rand();
}

ACardPlace* ACardGameMode::GetEnemyHPPlace()
{
	return EnemyHPPlace;
}

ACardPlace* ACardGameMode::GetPlayerHPPlace()
{
	return PlayerHPPlace;
}


ACardPlace* ACardGameMode::GetPlayerPlacedCard(int index)
{
	return PlayerPlacedCards[index];
}

ACardPlace* ACardGameMode::GetEnemyPlacedCard(int index)
{
	return EnemyPlacedCards[index];
}

ACardPlace* ACardGameMode::GetPlayerHandCard(int index)
{
	return PlayerHandCards[index];
}

ACardPlace* ACardGameMode::GetEnemyHandCard(int index)
{
	return EnemyHandCards[index];
}

TArray<ACardPlace*> ACardGameMode::GetPlayerPlaces()
{
	return PlayerPlacedCards;
}

TArray<ACardPlace*> ACardGameMode::GetEnemyPlaces()
{
	return EnemyPlacedCards;
}

TArray<ACardPlace*> ACardGameMode::GetPlayerHandCards() {
	return PlayerHandCards;
}

TArray<ACardPlace*> ACardGameMode::GetEnemyHandCards() {
	return EnemyHandCards;
}

bool ACardGameMode::IsPlayersTurn()
{
	return bIsPlayersTurn;
}

int ACardGameMode::GetIndexEnemyHandCard()
{
	for (int i{}; i < EnemyHandCards.Num(); ++i)
		if (!EnemyHandCards[i]->IsEmptyPlace())
			return i;

	return -1;
}

void ACardGameMode::EnemyWantsToPlay()
{
	int count = rand() % 2 + 2;

	int i{};
	if (PlayerHPPlace->GetCard()->HP > EnemyHPPlace->GetCard()->HP)
		// ищет пустые места у себя на столе (защита)
		for (i = 0; i < count; ++i)
		{
			int indexCard = GetIndexEnemyHandCard();
			if (indexCard == -1)
			{
				ChangeTurn();
				return;
			}
			int maxDamage{}; int indexMaxDam{};
			for (int j{}; j < 3; ++j)
				if (!PlayerPlacedCards[j]->IsEmptyPlace() && EnemyPlacedCards[j]->IsEmptyPlace())
					if (PlayerPlacedCards[j]->GetCard()->Damage > maxDamage)
					{
						maxDamage = PlayerPlacedCards[j]->GetCard()->Damage;
						indexMaxDam = j;
					}

			if (maxDamage != 0)
			{
				EnemyHandCards[indexCard]->GetCard()->BattleCry();
				EnemyPlacedCards[indexMaxDam]->SetAndMoveCard(EnemyHandCards[indexCard]->PickUp());
				--count;
			}
			else
				break;
		}
	else // ищет пустые места у противника (атака)
		for (i = 0; i < count; ++i)
		{
			int indexCard = GetIndexEnemyHandCard();
			if (indexCard == -1)
			{
				ChangeTurn();
				return;
			}
			for (int j{}; j < 3; ++j)
				if (PlayerPlacedCards[j]->IsEmptyPlace() && EnemyPlacedCards[j]->IsEmptyPlace())
				{
					EnemyHandCards[indexCard]->GetCard()->BattleCry();
					EnemyPlacedCards[j]->SetAndMoveCard(EnemyHandCards[indexCard]->PickUp());
					--count;
					break;
				}
				else
					if (j == 2)
						break;
		}

	for (i = 0; i < count; ++i)
	{
		int indexCard = GetIndexEnemyHandCard();
		if (indexCard == -1)
		{
			ChangeTurn();
			return;
		}
		int indexPlace = rand() % 3;
		if (EnemyPlacedCards[indexPlace]->IsEmptyPlace())
		{
			EnemyHandCards[indexCard]->GetCard()->BattleCry();
			EnemyPlacedCards[indexPlace]->SetAndMoveCard(EnemyHandCards[indexCard]->PickUp());
		}
		else
			for (int j{}; j < 3; ++j)
				if (EnemyPlacedCards[j]->IsEmptyPlace())
				{
					EnemyHandCards[indexCard]->GetCard()->BattleCry();
					EnemyPlacedCards[j]->SetAndMoveCard(EnemyHandCards[indexCard]->PickUp());
					break;
				}
	}
	ChangeTurn();
}


void ACardGameMode::EndTurn()
{
	for (int i{}; i < 3; ++i)
	{
		ACard* EnemyCard = EnemyPlacedCards[i]->GetCard();
		ACard* PlayerCard = PlayerPlacedCards[i]->GetCard();

		if (EnemyCard != nullptr && PlayerCard != nullptr)
		{
			AttackEachOther(EnemyCard, PlayerCard);
			if (PlayerCard->isDead())
				PlayerPlacedCards[i]->DestroyCard();
			else 
				this->ReturnToDeck(PlayerPlacedCards[i]);

			if (EnemyCard->isDead())
				EnemyPlacedCards[i]->DestroyCard();
			else
				this->ReturnToDeck(EnemyPlacedCards[i]);

			// карты возвращаются в деку
		}
		else
		{
			if (EnemyCard != nullptr)
			{
				EnemyCard->Attack(PlayerHPPlace->GetCard());
				if (PlayerHPPlace->GetCard()->isDead())
					EndCardGame(); // конец игры
			}
			else if (PlayerCard != nullptr)
			{
				PlayerCard->Attack(EnemyHPPlace->GetCard());
				if (EnemyHPPlace->GetCard()->isDead())
					EndCardGame(); // конец игры
			}
		}
	}
}

//bool ACardGameMode::AttackToFace(ACard* DamageCauser, ACard* DamageRecipient)
//{
//	DamageCauser->AttackToFace(DamageRecipient);
//	if (DamageRecipient->isDead())
//	{
//		DamageRecipient->Destroy();
//		return true;
//	}
//	else
//		return false;
//}

void ACardGameMode::ChangeTurn()
{
	if (bIsPlayersTurn)
	{
		EndTurn();
		bIsPlayersTurn = false;
	}
	else
		bIsPlayersTurn = true;
}

void ACardGameMode::EndCardGame()
{
	bReturnToMainLocation = true;
}