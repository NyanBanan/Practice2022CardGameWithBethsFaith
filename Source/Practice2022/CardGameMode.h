// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CardPlace.h"
#include "TimerManager.h"
#include "CardGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE2022_API ACardGameMode : public AGameModeBase // by глупая девочка
{
	GENERATED_BODY()

public:
	ACardGameMode();
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	ACardPlace* GetEnemyHPPlace();
	UFUNCTION(BlueprintCallable)
	ACardPlace* GetPlayerHPPlace();


	UFUNCTION(BlueprintCallable)
	ACardPlace* GetPlayerPlacedCard(int index);
	UFUNCTION(BlueprintCallable)
	ACardPlace* GetEnemyPlacedCard(int index);
	UFUNCTION(BlueprintCallable)
	ACardPlace* GetPlayerHandCard(int index);
	UFUNCTION(BlueprintCallable)
	ACardPlace* GetEnemyHandCard(int index);

	UFUNCTION(BlueprintCallable)
	TArray<ACardPlace*> GetPlayerHandCards();
	UFUNCTION(BlueprintCallable)
	TArray<ACardPlace*> GetEnemyHandCards();

	UFUNCTION(BlueprintCallable)
	TArray<ACardPlace*> GetPlayerPlaces();
	UFUNCTION(BlueprintCallable)
	TArray<ACardPlace*> GetEnemyPlaces();

	bool IsPlayersTurn();

	UFUNCTION(BlueprintCallable)
	void ChangeTurn();                                              // сменить очередь игрока/противника

	UFUNCTION(BlueprintCallable)
	void EnemyWantsToPlay();										// враг разыгрывает карты

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ReturnToDeck(ACardPlace* iPlace);

	UFUNCTION(BlueprintCallable)
	void EndCardGame();                                             // конец карточный игры (переход на первую локацию)

	//bool AttackToFace(ACard* DamageCauser, ACard* DamageRecipient);// возвращает true если после атаки оппонент мертв

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bReturnToMainLocation=false;                                // true если игра завершена и нужно вернуться в начальную локацию

private:
	ACardPlace* PlayerHPPlace;                                      // место для карты здоровья игрока
	ACardPlace* EnemyHPPlace;                                       // место для карты здоровья врага

	TArray<ACardPlace*> PlayerPlacedCards;                          // места для карт игрока
	TArray<ACardPlace*> EnemyPlacedCards;                           // места для карт противника
	TArray<ACardPlace*> PlayerHandCards;							// места в руке игрока
	TArray<ACardPlace*> EnemyHandCards;								// места в руке противника

	bool bIsPlayersTurn = false;                                    // ход игрока?

	void EndTurn();                                                 // конец хода обоих игроков

	int GetIndexEnemyHandCard();                                    // даёт карту (с проверкой на непустоту) из руки врага
};
