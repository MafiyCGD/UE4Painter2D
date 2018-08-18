// Fill out your copyright notice in the Description page of Project Settings.

#include "Painter2DEditorViewportClient.h"
#include "CanvasItem.h"
#include "CanvasTypes.h"
#include "Widgets/Layout/SScrollBar.h"
#include "Slate/SceneViewport.h"
#include "Widgets/Painter2DEditorEditorViewport.h"
#include "IPainter2DEditorToolkit.h"
#include "Painter2DAsset.h"

FPainter2DEditorViewportClient::FPainter2DEditorViewportClient(TWeakPtr<IPainter2DEditorToolkit> InPainter2DEditor, TWeakPtr<SPainter2DEditorEditorViewport> InPainter2DEditorViewport) :
	Painter2DEditorPtr(InPainter2DEditor),
	Painter2DEditorViewportPtr(InPainter2DEditorViewport),
	ClearColor(0.15f, 0.15f, 0.15f)
{
	CanvasData = Painter2DEditorPtr.Pin()->GetPainter2DAsset()->GetCanvas();

	CanvasWeight = CanvasData->GetSizeX();
	CanvasHeight = CanvasData->GetSizeX();
}

void FPainter2DEditorViewportClient::Draw(FViewport* Viewport, FCanvas* Canvas)
{
	const FVector2D& Ratio = FVector2D(GetViewportHorizontalScrollBarRatio(), GetViewportVerticalScrollBarRatio());
	const FVector2D& ViewportSize = FVector2D(Painter2DEditorViewportPtr.Pin()->GetViewport()->GetSizeXY().X, Painter2DEditorViewportPtr.Pin()->GetViewport()->GetSizeXY().Y);
	const FVector2D& ScrollBarPos = GetViewportScrollBarPositions();
	int32 YOffset = (Ratio.Y > 1.0f) ? ((ViewportSize.Y - (ViewportSize.Y / Ratio.Y)) * 0.5f) : 0;
	int32 YPos = YOffset - ScrollBarPos.Y;
	int32 XOffset = (Ratio.X > 1.0f) ? ((ViewportSize.X - (ViewportSize.X / Ratio.X)) * 0.5f) : 0;
	int32 XPos = XOffset - ScrollBarPos.X;

	UpdateScrollBars();

	Canvas->Clear(ClearColor);

	if (CanvasData->Resource != nullptr)
	{
		FCanvasTileItem TileItem(FVector2D(XPos, YPos), CanvasData->Resource, FVector2D((float)CanvasWeight, (float)CanvasHeight), FLinearColor(1.0f, 1.0f, 1.0f));
		Canvas->DrawItem(TileItem);
	}
}

void FPainter2DEditorViewportClient::UpdateScrollBars()
{
	TSharedPtr<SPainter2DEditorEditorViewport> Viewport = Painter2DEditorViewportPtr.Pin();

	if (!Viewport.IsValid() || !Viewport->GetVerticalScrollBar().IsValid() || !Viewport->GetHorizontalScrollBar().IsValid())
	{
		return;
	}

	float VRatio = GetViewportVerticalScrollBarRatio();
	float HRatio = GetViewportHorizontalScrollBarRatio();
	float VDistFromBottom = Viewport->GetVerticalScrollBar()->DistanceFromBottom();
	float HDistFromBottom = Viewport->GetHorizontalScrollBar()->DistanceFromBottom();

	if (VRatio < 1.0f)
	{
		if (VDistFromBottom < 1.0f)
		{
			Viewport->GetVerticalScrollBar()->SetState(FMath::Clamp(1.0f - VRatio - VDistFromBottom, 0.0f, 1.0f), VRatio);
		}
		else
		{
			Viewport->GetVerticalScrollBar()->SetState(0.0f, VRatio);
		}
	}

	if (HRatio < 1.0f)
	{
		if (HDistFromBottom < 1.0f)
		{
			Viewport->GetHorizontalScrollBar()->SetState(FMath::Clamp(1.0f - HRatio - HDistFromBottom, 0.0f, 1.0f), HRatio);
		}
		else
		{
			Viewport->GetHorizontalScrollBar()->SetState(0.0f, HRatio);
		}
	}
}

float FPainter2DEditorViewportClient::GetViewportVerticalScrollBarRatio() const
{
	float WidgetHeight = 1.0f;
	if (Painter2DEditorViewportPtr.Pin()->GetVerticalScrollBar().IsValid())
	{
		WidgetHeight = Painter2DEditorViewportPtr.Pin()->GetViewport()->GetSizeXY().Y;
	}

	return WidgetHeight / CanvasHeight;
}


float FPainter2DEditorViewportClient::GetViewportHorizontalScrollBarRatio() const
{
	float WidgetWidth = 1.0f;
	if (Painter2DEditorViewportPtr.Pin()->GetHorizontalScrollBar().IsValid())
	{
		WidgetWidth = Painter2DEditorViewportPtr.Pin()->GetViewport()->GetSizeXY().X;
	}

	return WidgetWidth / CanvasWeight;
}

FVector2D FPainter2DEditorViewportClient::GetViewportScrollBarPositions() const
{
	FVector2D Positions = FVector2D::ZeroVector;
	if (Painter2DEditorViewportPtr.Pin()->GetVerticalScrollBar().IsValid() && Painter2DEditorViewportPtr.Pin()->GetHorizontalScrollBar().IsValid())
	{
		float VRatio = GetViewportVerticalScrollBarRatio();
		float HRatio = GetViewportHorizontalScrollBarRatio();
		float VDistFromBottom = Painter2DEditorViewportPtr.Pin()->GetVerticalScrollBar()->DistanceFromBottom();
		float HDistFromBottom = Painter2DEditorViewportPtr.Pin()->GetHorizontalScrollBar()->DistanceFromBottom();

		if ((Painter2DEditorViewportPtr.Pin()->GetVerticalScrollBar()->GetVisibility() == EVisibility::Visible) && VDistFromBottom < 1.0f)
		{
			Positions.Y = FMath::Clamp(1.0f - VRatio - VDistFromBottom, 0.0f, 1.0f) * CanvasHeight;
		}
		else
		{
			Positions.Y = 0.0f;
		}

		if ((Painter2DEditorViewportPtr.Pin()->GetHorizontalScrollBar()->GetVisibility() == EVisibility::Visible) && HDistFromBottom < 1.0f)
		{
			Positions.X = FMath::Clamp(1.0f - HRatio - HDistFromBottom, 0.0f, 1.0f) * CanvasWeight;
		}
		else
		{
			Positions.X = 0.0f;
		}
	}

	return Positions;
}