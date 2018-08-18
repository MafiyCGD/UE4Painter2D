// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Painter2DAsset.generated.h"

class UTexture2D;

/**
 * 
 */
UCLASS()
class PAINTER2D_API UPainter2DAsset : public UObject
{
	GENERATED_BODY()

public:

	void InitializeCanvas(const uint32 sizeX, const uint32 sizeY);

	TWeakObjectPtr<UTexture2D> GetCanvas() const;

	void UpdateCanvas();

private:
	TWeakObjectPtr<UTexture2D> DynamicCanvas;

	TSharedPtr<FUpdateTextureRegion2D> UpdateTextureRegion2D;

	int32 CanvasWidth;

	int32 CanvasHeight;

	uint32 Data_PixelSize;

	int32 BufferPitch;

	// The current data array
	TArray<FColor> CanvasPixels;
};
