// Fill out your copyright notice in the Description page of Project Settings.

#include "Painter2DAssetEditor.h"

FPainter2DAssetEditor::FPainter2DAssetEditor()
{
}

void FPainter2DAssetEditor::RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(TabManager);
}

void FPainter2DAssetEditor::UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(TabManager);
}

void FPainter2DAssetEditor::InitEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, const TArray<UObject *>& ObjectsToEdit)
{
	const TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout("CustomEditor_Layout");
	StandaloneDefaultLayout->AddArea(FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical));
	FAssetEditorToolkit::InitAssetEditor(Mode, InitToolkitHost, "Painter2D", StandaloneDefaultLayout, true, true, ObjectsToEdit);
}

FName FPainter2DAssetEditor::GetToolkitFName() const
{
	return FName("Painter2D");
}

FText FPainter2DAssetEditor::GetBaseToolkitName() const
{
	return FText::FromString(TEXT("Painter2D"));
}

FLinearColor FPainter2DAssetEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor::White;
}

FString FPainter2DAssetEditor::GetWorldCentricTabPrefix() const
{
	return FString("Painter2D");
}