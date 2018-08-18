// Fill out your copyright notice in the Description page of Project Settings.

#include "Painter2DAssetEditor.h"
#include "Widgets/Painter2DEditorEditorViewport.h"
#include "Widgets/Docking/SDockTab.h"
#include "EditorStyleSet.h"
#include "Painter2DAsset.h"

#define LOCTEXT_NAMESPACE "FPainter2DAssetEditor"

const FName FPainter2DAssetEditor::ViewportTabId(TEXT("Painter2D_Viewport"));

FPainter2DAssetEditor::FPainter2DAssetEditor()
{
}

void FPainter2DAssetEditor::RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	WorkspaceMenuCategory = TabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_Painter2DEditor", "Painter2D Editor"));
	auto WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();

	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	TabManager->RegisterTabSpawner(ViewportTabId, FOnSpawnTab::CreateSP(this, &FPainter2DAssetEditor::HandleTabSpawnerSpawnViewport))
		.SetDisplayName(LOCTEXT("ViewportTab", "Viewport"))
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Viewports"));
}

void FPainter2DAssetEditor::UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);

	InTabManager->UnregisterTabSpawner(ViewportTabId);
}

void FPainter2DAssetEditor::InitEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UPainter2DAsset* Painter2DAsset)
{
	Painter2DAssetPtr = Painter2DAsset;
	VieportPtr = SNew(SPainter2DEditorEditorViewport, SharedThis(this));
	const TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout("Painter2DEditor_Layout");
	StandaloneDefaultLayout->AddArea
	(
		FTabManager::NewPrimaryArea()
		->SetOrientation(Orient_Horizontal)
		->Split
		(
			FTabManager::NewSplitter()
			->SetOrientation(Orient_Vertical)
			->SetSizeCoefficient(0.66f)
			->Split
			(
				FTabManager::NewStack()
				->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
				->SetHideTabWell(true)
				->SetSizeCoefficient(0.1f)
			)
			->Split
			(
				FTabManager::NewStack()
				->AddTab(ViewportTabId, ETabState::OpenedTab)
				->SetHideTabWell(true)
				->SetSizeCoefficient(0.9f)
			)
		)
	);

	FAssetEditorToolkit::InitAssetEditor(Mode, InitToolkitHost, "Painter2D", StandaloneDefaultLayout, true, true, Painter2DAsset);
}

TWeakObjectPtr<UPainter2DAsset> FPainter2DAssetEditor::GetPainter2DAsset()
{
	return Painter2DAssetPtr;
}

TSharedRef<SDockTab> FPainter2DAssetEditor::HandleTabSpawnerSpawnViewport(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId() == ViewportTabId);

	return SNew(SDockTab)
		.Label(LOCTEXT("FPainter2DAssetEditor", "Viewport"))
		[
			VieportPtr.ToSharedRef()
		];
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

#undef  LOCTEXT_NAMESPACE// "Painter2DViewportTitle"