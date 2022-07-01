// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"

void AMyHUD::DrawHUD()
{
	Super::DrawHUD();

	for (int c = messages.Num() - 1; c >= 0; c--)
	{
		float outputWidth, outputHeight, pad = 20.f;
		GetTextSize(messages[c].message, outputWidth, outputHeight, hudFont,
			1.f);
		float messageH = outputHeight + 2.f * pad;
		float x = 0.f, y = c * messageH;

		DrawRect(FLinearColor::Black, x, y, Canvas->SizeX, messageH);
		
		DrawText(messages[c].message, messages[c].color, x + 3*pad, y + pad,
			hudFont);
	
		if (messages[c].tex!= nullptr)
			DrawTexture(messages[c].tex, x, y, messageH, messageH, 0, 0, 1, 1);

		messages[c].time -= GetWorld()->GetDeltaSeconds();
		
		if (messages[c].time < 0)
		{
			messages.RemoveAt(c);
		}
	}
}
void AMyHUD::addMessage(FMessage msg)
{
	messages.Add(msg);
}
