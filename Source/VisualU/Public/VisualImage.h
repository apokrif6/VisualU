// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Components/Widget.h"
#include "Engine/StreamableManager.h"
#include "VisualImage.generated.h"

class UPaperFlipbook;
class UPaperSprite;
class SVisualImage;

/**
 * Widget that can visualize paper flipbook either as animation or as static image
 */
UCLASS()
class VISUALU_API UVisualImage : public UWidget
{
	GENERATED_BODY()

public:

	UVisualImage(const FObjectInitializer& ObjectInitializer);

	DECLARE_DYNAMIC_DELEGATE_RetVal(UPaperFlipbook*, FGetPaperFlipbook);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appearance", BlueprintGetter = GetFlipbook)
	mutable UPaperFlipbook* Flipbook; //TODO: Change this to a strong reference

	UPROPERTY()
	FGetPaperFlipbook FlipbookDelegate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appearance", BlueprintGetter = GetColorAndOpacity)
	FLinearColor ColorAndOpacity;

	UPROPERTY()
	FGetLinearColor ColorAndOpacityDelegate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appearance", BlueprintGetter = GetDesiredScale, meta = (Delta = 0.25f, UIMin = 0, ClampMin = 0, AllowPreserveRatio))
	FVector2D DesiredScale;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appearance", BlueprintGetter = GetMirrorScale, meta = (ToolTip = "Determines the orientation of the sprite on both axes", Delta = 1.f, UIMin = -1, UIMax = 1, ClampMin = -1, ClampMax = 1))
	FVector2D MirrorScale;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appearance", BlueprintGetter = IsAnimated, meta = (ToolTip = "Decides whether or not flipbook should be played"))
	bool bAnimate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appearance", BlueprintGetter = GetFrameIndex, meta = (ToolTip = "Index of the flipbook's frame that must be rendered", EditCondition = "!bAnimate", EditConditionHides))
	int FrameIndex;

	TSharedPtr<FStreamableHandle> StreamingHandle;

public:
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Visual Image")
	void SetAnimate(bool IsAnimated);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Visual Image")
	void SetFrameIndex(int Index);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Visual Image")
	void SetFlipbook(UPaperFlipbook* InFlipbook);

	void SetFlipbook(TObjectPtr<UPaperFlipbook> InFlipbook);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Visual Image")
	void SetFlipbookAsync(TSoftObjectPtr<UPaperFlipbook> InFlipbook);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Visual Image")
	void CancelAsyncLoad();

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Visual Image")
	bool IsFlipbookLoading() const;

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Visual Image")
	bool IsFlipbookLoaded() const;

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Visual Image")
	void SetColorAndOpacity(const FLinearColor& InColorAndOpacity);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Visual Image")
	void SetDesiredScale(const FVector2D& InDesiredScale);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Visual Image")
	void SetMirrorScale(const FVector2D& InMirrorScale);

	UFUNCTION(BlueprintGetter)
	FORCEINLINE UPaperFlipbook* GetFlipbook() const { return Flipbook; }

	UFUNCTION(BlueprintGetter)
	FORCEINLINE bool IsAnimated() const { return bAnimate; }

	UFUNCTION(BlueprintGetter)
	FORCEINLINE int GetFrameIndex() const { return FrameIndex; }

	UFUNCTION(BlueprintGetter)
	FORCEINLINE FLinearColor GetColorAndOpacity() const { return ColorAndOpacity; }

	UFUNCTION(BlueprintGetter)
	FORCEINLINE FVector2D GetDesiredScale() const { return DesiredScale; }

	UFUNCTION(BlueprintGetter)
	FORCEINLINE FVector2D GetMirrorScale() const { return MirrorScale; }

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Visual Image")
	UPaperSprite* GetCurrentSprite() const;

protected:
#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif

	virtual void SynchronizeProperties() override;

	virtual TSharedRef<SWidget> RebuildWidget() override;

	virtual void TryAsyncLoad(TSoftObjectPtr<UPaperFlipbook> SoftFlipbook, FStreamableDelegate AfterLoadDelegate);

	const UPaperFlipbook* ToFlipbook(TAttribute<UPaperFlipbook*> InFlipbook) const;

	PROPERTY_BINDING_IMPLEMENTATION(FSlateColor, ColorAndOpacity);

private:
	TSharedPtr<SVisualImage> VisualImageSlate;
};