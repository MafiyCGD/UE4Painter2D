// Fill out your copyright notice in the Description page of Project Settings.
#include "Painter2DAssetTypeActions.h"
#include "Painter2DAsset.h"
#include "Painter2DEditor/Painter2DAssetEditor.h"

FPainter2DAssetTypeActions::FPainter2DAssetTypeActions(EAssetTypeCategories::Type InAssetCategory)
	: MyAssetCategory(InAssetCategory)
{
}

FText FPainter2DAssetTypeActions::GetName() const
{
	return FText::FromString(TEXT("Painter2D"));
}

FColor FPainter2DAssetTypeActions::GetTypeColor() const
{
	return FColor::Cyan;
}

UClass* FPainter2DAssetTypeActions::GetSupportedClass() const
{
	return UPainter2DAsset::StaticClass();
}

void FPainter2DAssetTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
	const EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		if (UPainter2DAsset* Sprite = Cast<UPainter2DAsset>(*ObjIt))
		{
			TSharedRef<FPainter2DAssetEditor> NewSpriteEditor(new FPainter2DAssetEditor());
			NewSpriteEditor->InitEditor(Mode, EditWithinLevelEditor, InObjects);
		}
	}
}

uint32 FPainter2DAssetTypeActions::GetCategories()
{
	return MyAssetCategory;
}