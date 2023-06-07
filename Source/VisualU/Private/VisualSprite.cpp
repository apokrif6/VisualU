// Fill out your copyright notice in the Description page of Project Settings.


#include "VisualSprite.h"
#include "Blueprint/WidgetTree.h"
#include "VisualDefaults.h"
#include "VisualImage.h"
#include "PaperFlipbook.h"
#include "Animation/WidgetAnimation.h"

UVisualSprite::UVisualSprite(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UVisualSprite::AssignExpressions(const TArray<TSoftObjectPtr<UPaperFlipbook>>& InExpressions)
{
	if (InExpressions.IsEmpty())
	{
		return;
	}
	TArray<UWidget*> ChildWidgets;
	WidgetTree->GetChildWidgets(GetRootWidget(), ChildWidgets);

	int i, j;
	for (i = j = 0; i < ChildWidgets.Num(); i++)
	{
		UWidget* Child = ChildWidgets[i];
		if (Child->IsA<UVisualImage>())
		{
			UVisualImage* ChildImage = Cast<UVisualImage>(Child);
			TSoftObjectPtr<UPaperFlipbook> Flipbook = InExpressions[j];
			ChildImage->SetFlipbookAsync(Flipbook);
			j++;
		}
	}
}