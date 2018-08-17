// Fill out your copyright notice in the Description page of Project Settings.

#include "Painter2DEditorEditorViewport.h"
#include "Models/Painter2DEditorViewportClient.h"
#include "Slate/SceneViewport.h"
#include "Widgets/SViewport.h"
#include "Widgets/Layout/SScrollBar.h"

#include "IPainter2DEditorToolkit.h"

void SPainter2DEditorEditorViewport::Construct(const FArguments& InArgs, const TSharedRef<IPainter2DEditorToolkit>& InToolkit)
{
	ToolkitPtr = InToolkit;
	this->ChildSlot
	[
		SNew(SVerticalBox)
			+SVerticalBox::Slot()
			.FillHeight(1.0f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
					.FillWidth(1.0f)
					[
						SNew(SOverlay)

						// viewport canvas
						+ SOverlay::Slot()
						[
							SAssignNew(ViewportWidget, SViewport)
							.EnableGammaCorrection(false)
						]
					]
				
				+ SHorizontalBox::Slot()
					.AutoWidth()
					[
						// vertical scroll bar
						SAssignNew(Painter2DViewportVerticalScrollBar, SScrollBar)
						.Visibility(this, &SPainter2DEditorEditorViewport::HandleVerticalScrollBarVisibility)
						.OnUserScrolled(this, &SPainter2DEditorEditorViewport::HandleVerticalScrollBarScrolled)
					]
			]

		+ SVerticalBox::Slot()
			.AutoHeight()
			[
				// horizontal scrollbar
				SAssignNew(Painter2DViewportHorizontalScrollBar, SScrollBar)
				.Orientation(Orient_Horizontal)
				.Visibility(this, &SPainter2DEditorEditorViewport::HandleHorizontalScrollBarVisibility)
				.OnUserScrolled(this, &SPainter2DEditorEditorViewport::HandleHorizontalScrollBarScrolled)
			]
	];


	ViewportClient = MakeShareable(new FPainter2DEditorViewportClient(SharedThis(this)));

	Viewport = MakeShareable(new FSceneViewport(ViewportClient.Get(), ViewportWidget));

	// The viewport widget needs an interface so it knows what should render
	ViewportWidget->SetViewportInterface(Viewport.ToSharedRef());
}

TSharedPtr<FSceneViewport> SPainter2DEditorEditorViewport::GetViewport() const
{
	return Viewport;
}

void SPainter2DEditorEditorViewport::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	Viewport->Invalidate();
	Viewport->InvalidateDisplay();
}

TSharedPtr<SScrollBar> SPainter2DEditorEditorViewport::GetVerticalScrollBar() const
{
	return Painter2DViewportVerticalScrollBar;
}

TSharedPtr<SScrollBar> SPainter2DEditorEditorViewport::GetHorizontalScrollBar() const
{
	return Painter2DViewportHorizontalScrollBar;
}

void SPainter2DEditorEditorViewport::HandleHorizontalScrollBarScrolled(float InScrollOffsetFraction)
{
	float Ratio = ViewportClient->GetViewportHorizontalScrollBarRatio();
	float MaxOffset = (Ratio < 1.0f) ? 1.0f - Ratio : 0.0f;
	InScrollOffsetFraction = FMath::Clamp(InScrollOffsetFraction, 0.0f, MaxOffset);

	Painter2DViewportHorizontalScrollBar->SetState(InScrollOffsetFraction, Ratio);
}


EVisibility SPainter2DEditorEditorViewport::HandleHorizontalScrollBarVisibility() const
{
	if (ViewportClient->GetViewportHorizontalScrollBarRatio() < 1.0f)
	{
		return EVisibility::Visible;
	}

	return EVisibility::Collapsed;
}


void SPainter2DEditorEditorViewport::HandleVerticalScrollBarScrolled(float InScrollOffsetFraction)
{
	float Ratio = ViewportClient->GetViewportVerticalScrollBarRatio();
	float MaxOffset = (Ratio < 1.0f) ? 1.0f - Ratio : 0.0f;
	InScrollOffsetFraction = FMath::Clamp(InScrollOffsetFraction, 0.0f, MaxOffset);

	Painter2DViewportVerticalScrollBar->SetState(InScrollOffsetFraction, Ratio);
}


EVisibility SPainter2DEditorEditorViewport::HandleVerticalScrollBarVisibility() const
{
	if (ViewportClient->GetViewportVerticalScrollBarRatio() < 1.0f)
	{
		return EVisibility::Visible;
	}

	return EVisibility::Collapsed;
}