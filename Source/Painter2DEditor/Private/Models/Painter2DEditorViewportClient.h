// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnrealClient.h"

class SPainter2DEditorEditorViewport;
class IPainter2DEditorToolkit;
/**
 * 
 */
class FPainter2DEditorViewportClient 
	: public FViewportClient
{
public:
	/** Constructor */
	FPainter2DEditorViewportClient(TWeakPtr<IPainter2DEditorToolkit> InPainter2DEditor, TWeakPtr<SPainter2DEditorEditorViewport> InPainter2DEditorViewport);
	~FPainter2DEditorViewportClient() {};

	/** FViewportClient interface */
	virtual void Draw(FViewport* Viewport, FCanvas* Canvas) override;

	/** Returns the ratio of the size of the Texture texture to the size of the viewport */
	float GetViewportVerticalScrollBarRatio() const;
	float GetViewportHorizontalScrollBarRatio() const;

private:
	/** Default render clear color */
	FLinearColor ClearColor;
	uint32 CanvasWeight;
	uint32 CanvasHeight;

	TWeakObjectPtr<UTexture2D> CanvasData;

	/** Pointer back to the Painter2D editor tool that owns us */
	TWeakPtr<IPainter2DEditorToolkit> Painter2DEditorPtr;

	/** Pointer back to the Painter2D viewport control that owns us */
	TWeakPtr<SPainter2DEditorEditorViewport> Painter2DEditorViewportPtr;

	/** Returns the positions of the scrollbars relative to the Texture textures */
	FVector2D GetViewportScrollBarPositions() const;
	/** Updates the states of the scrollbars */
	void UpdateScrollBars();

};
