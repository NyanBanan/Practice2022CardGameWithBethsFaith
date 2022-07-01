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
class PRACTICE2022_API ACardGameMode : public AGameModeBase // by ������ �������
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
	void ChangeTurn();                                              // ������� ������� ������/����������

	UFUNCTION(BlueprintCallable)
	void EnemyWantsToPlay();										// ���� ����������� �����

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ReturnToDeck(ACardPlace* iPlace);

	UFUNCTION(BlueprintCallable)
	void EndCardGame();                                             // ����� ��������� ���� (������� �� ������ �������)

	//bool AttackToFace(ACard* DamageCauser, ACard* DamageRecipient);// ���������� true ���� ����� ����� �������� �����

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bReturnToMainLocation=false;                                // true ���� ���� ��������� � ����� ��������� � ��������� �������

private:
	ACardPlace* PlayerHPPlace;                                      // ����� ��� ����� �������� ������
	ACardPlace* EnemyHPPlace;                                       // ����� ��� ����� �������� �����

	TArray<ACardPlace*> PlayerPlacedCards;                          // ����� ��� ���� ������
	TArray<ACardPlace*> EnemyPlacedCards;                           // ����� ��� ���� ����������
	TArray<ACardPlace*> PlayerHandCards;							// ����� � ���� ������
	TArray<ACardPlace*> EnemyHandCards;								// ����� � ���� ����������

	bool bIsPlayersTurn = false;                                    // ��� ������?

	void EndTurn();                                                 // ����� ���� ����� �������

	int GetIndexEnemyHandCard();                                    // ��� ����� (� ��������� �� ���������) �� ���� �����
};
