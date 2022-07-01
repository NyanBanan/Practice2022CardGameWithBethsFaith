// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCardController.h"
#include "CardGameMode.h"
#include "CardGameCamera.h"


// авторство глупой девочки

void APlayerCardController::SetupInputComponent()
{
    Super::SetupInputComponent();
	InputComponent->BindAction("LeftClick", IE_Pressed, this, &APlayerCardController::OnMouseClick);
    InputComponent->BindAction("RightClick", IE_Pressed, this, &APlayerCardController::ZoomCard);
}

void APlayerCardController::OnMouseClick()
{
    ACardGameCamera* CardPlayer = Cast<ACardGameCamera>(this->GetPawn());
    ACardGameMode* GameMode = (ACardGameMode*)UGameplayStatics::GetGameMode(this);
    if (CardPlayer == nullptr || GameMode == nullptr)
        return;
    if (GameMode->IsPlayersTurn() == false)
        return;
    if (CardPlayer->GetZoomedCard() != nullptr)
        this->ZoomCard();

    FHitResult HitResult;
    GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, false, HitResult);

    // выбрана карта, камера первая
    if (Cast<ACard>(HitResult.GetActor()) != nullptr && CardPlayer->GetCameraNumber() == 0)
    {
        CardPlayer->NextCamera();

        ACard* Card = Cast<ACard>(HitResult.GetActor());
        CardPlayer->SetSelectedCard(Card);
        Card->MoveAndRotate(1040, -270, 850, 0, 90, 0);
    }

    // выбрано место карты, камера вторая, есть выбранная карта
    if (CardPlayer->GetCameraNumber() == 1 && Cast<ACardPlace>(HitResult.GetActor()) != nullptr
        && CardPlayer->GetSelectedCard() != nullptr)
    {
        ACardPlace* CPlace = (ACardPlace*)(HitResult.GetActor());
        if (CPlace->bIsPlayersPlace == false || !CPlace->IsEmptyPlace())
            return;

        CardPlayer->GetSelectedCard()->BattleCry();
        CPlace->SetAndMoveCard(CardPlayer->GetSelectedCard());

        // освободить место в руке, где лежала выбранная картаa
        for (int i{}; i < 4; ++i)
            if (GameMode->GetPlayerHandCard(i)->GetCard() == CardPlayer->GetSelectedCard())
            {
                GameMode->GetPlayerHandCard(i)->ToFree();
                break;
            }

        CardPlayer->SetSelectedCard(nullptr);
    }
}

void APlayerCardController::ZoomCard() {
    ACardGameCamera* CardPlayer = Cast<ACardGameCamera>(this->GetPawn());
    if (CardPlayer == nullptr)
        return;
    /*if (CardPlayer->GetSelectedCard() != nullptr)
        this->OnMouseClick();*/
    if (CardPlayer->GetZoomedCard() != nullptr) {
        FVector loc = CardPlayer->GetZoomedCard()->GetLastLocation();
        FRotator rot = CardPlayer->GetZoomedCard()->GetLastRotation();
        CardPlayer->GetZoomedCard()->MoveAndRotate(loc.X, loc.Y, loc.Z, rot.Pitch, rot.Yaw, rot.Roll);
        CardPlayer->SetZoomedCard(nullptr);
    }
    else {
        FHitResult HitResult;
        GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, false, HitResult);
        if (Cast<ACard>(HitResult.GetActor()) != nullptr) {
            ACard* Card = Cast<ACard>(HitResult.GetActor());
            switch (CardPlayer->GetCameraNumber())
            {
            case 0:
                Card->MoveAndRotate(-2040, 2380, 1620, 0, 90, 60);
                CardPlayer->SetZoomedCard(Card);
                break;
            case 1:
                Card->MoveAndRotate(1230, 1710, 2910, 0, 90, 20);
                CardPlayer->SetZoomedCard(Card);
                break;
            case 2:
                Card->MoveAndRotate(3740, 1700, 2030, 0, 90, 0);
                CardPlayer->SetZoomedCard(Card);
                break;
            default:
                break;
            }
        }
    }
}