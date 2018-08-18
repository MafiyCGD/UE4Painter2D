// Fill out your copyright notice in the Description page of Project Settings.

#include "Painter2DAsset.h"
#include "Engine/Texture2D.h"


void UPainter2DAsset::InitializeCanvas(const uint32 sizeX, const uint32 sizeY)
{
	CanvasWidth = sizeX;
	CanvasHeight = sizeY;
	DynamicCanvas = UTexture2D::CreateTransient(CanvasWidth, CanvasHeight);
	DynamicCanvas->UpdateResource();

	UpdateTextureRegion2D = MakeShareable(new FUpdateTextureRegion2D(0, 0, 0, 0, CanvasWidth, CanvasHeight));

	Data_PixelSize = sizeof(FColor);
	BufferPitch = CanvasWidth * Data_PixelSize;

	// Initialize data array 
	CanvasPixels.Init(FColor::White, CanvasWidth * CanvasWidth);

	UpdateCanvas();
}

void UPainter2DAsset::UpdateCanvas()
{
	if (UpdateTextureRegion2D.IsValid())
	{
		DynamicCanvas->UpdateTextureRegions((int32)0, (uint32)1, UpdateTextureRegion2D.Get(), (uint32)BufferPitch, (uint32)Data_PixelSize, (uint8*)CanvasPixels.GetData());
	}
}

TWeakObjectPtr<UTexture2D> UPainter2DAsset::GetCanvas() const
{
	return DynamicCanvas;
}
