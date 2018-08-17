// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"

class FSceneViewport;
class SViewport;
class SScrollBar;
class IPainter2DEditorToolkit;

/**
 * 
 */
class SPainter2DEditorEditorViewport : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SPainter2DEditorEditorViewport) { }
	SLATE_END_ARGS()

	/**
	* Constructs the widget.
	*
	* @param InArgs The construction arguments.
	*/
	void Construct(const FArguments& InArgs, const TSharedRef<IPainter2DEditorToolkit>& InToolkit);

	// SWidget overrides
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	TSharedPtr<FSceneViewport> GetViewport() const;
	TSharedPtr<SScrollBar> GetVerticalScrollBar() const;
	TSharedPtr<SScrollBar> GetHorizontalScrollBar() const;

private:
	// Callback for the horizontal scroll bar.
	void HandleHorizontalScrollBarScrolled(float InScrollOffsetFraction);

	// Callback for getting the visibility of the horizontal scroll bar.
	EVisibility HandleHorizontalScrollBarVisibility() const;

	// Callback for the vertical scroll bar.
	void HandleVerticalScrollBarScrolled(float InScrollOffsetFraction);

	// Callback for getting the visibility of the horizontal scroll bar.
	EVisibility HandleVerticalScrollBarVisibility() const;

	// Pointer back to the Texture editor tool that owns us.
	TWeakPtr<IPainter2DEditorToolkit> ToolkitPtr;

	// Level viewport client.
	TSharedPtr<class FPainter2DEditorViewportClient> ViewportClient;

	// Slate viewport for rendering and IO.
	TSharedPtr<FSceneViewport> Viewport;

	// Viewport widget.
	TSharedPtr<SViewport> ViewportWidget;

	// Vertical scrollbar.
	TSharedPtr<SScrollBar> Painter2DViewportVerticalScrollBar;

	// Horizontal scrollbar.
	TSharedPtr<SScrollBar> Painter2DViewportHorizontalScrollBar;
};
