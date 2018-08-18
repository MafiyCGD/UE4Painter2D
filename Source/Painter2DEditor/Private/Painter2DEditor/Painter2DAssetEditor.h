// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IPainter2DEditorToolkit.h"


class SPainter2DEditorEditorViewport;
class UPainter2DAsset;
/**
 * 
 */
class FPainter2DAssetEditor 
	: public IPainter2DEditorToolkit
{
public:
	FPainter2DAssetEditor();

	// IToolkit interface
	virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;
	// End of IToolkit interface

	// FAssetEditorToolkit
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	// End of FAssetEditorToolkit

	void InitEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UPainter2DAsset* Painter2DAsset);

	// Callback for spawning the Viewport tab.
	TSharedRef<SDockTab> HandleTabSpawnerSpawnViewport(const FSpawnTabArgs& Args);

	TWeakObjectPtr<UPainter2DAsset> GetPainter2DAsset() override;

private:
	TWeakObjectPtr<UPainter2DAsset> Painter2DAssetPtr;

	TSharedPtr<SPainter2DEditorEditorViewport> VieportPtr;

	// The name of the Viewport tab.
	static const FName ViewportTabId;
};
