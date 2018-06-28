// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Painter2DEditorModule.h"
#include "Core.h"
#include "ModuleManager.h"
#include "IPluginManager.h"
#include "Painter2DStyle.h"
#include "Painter2DAssetTypeActions.h"

#include "AssetToolsModule.h"

#define LOCTEXT_NAMESPACE "FPainter2DEditorModule"

void FPainter2DEditorModule::StartupModule()
{
	FPainter2DStyle::Initialize();

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	Painter2DAssetCategoryBit = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("Painter2D")), LOCTEXT("Painter2DAssetCategory", "Painter2D"));
	RegisterAssetTypeAction(AssetTools, MakeShareable(new FPainter2DAssetTypeActions(Painter2DAssetCategoryBit)));
}

void FPainter2DEditorModule::RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
{
	AssetTools.RegisterAssetTypeActions(Action);
	CreatedAssetTypeActions.Add(Action);
}

void FPainter2DEditorModule::ShutdownModule()
{
	FPainter2DStyle::Shutdown();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FPainter2DEditorModule, Painter2DEditor)