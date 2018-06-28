// Fill out your copyright notice in the Description page of Project Settings.

#include "Painter2DStyle.h"
#include "SlateStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "ClassIconFinder.h"
#include "IPluginManager.h"

#define IMAGE_PLUGIN_BRUSH( RelativePath, ... ) FSlateImageBrush( FPainter2DStyle::InContent( RelativePath, ".png" ), __VA_ARGS__ )

TSharedPtr< FSlateStyleSet > FPainter2DStyle::StyleSet = nullptr;
TSharedPtr< class ISlateStyle > FPainter2DStyle::Get() { return StyleSet; }

FString FPainter2DStyle::InContent(const FString& RelativePath, const ANSICHAR* Extension)
{
	static FString ContentDir = IPluginManager::Get().FindPlugin(TEXT("Painter2D"))->GetContentDir();
	return (ContentDir / RelativePath) + Extension;
}

FName FPainter2DStyle::GetStyleSetName()
{
	static FName Painter2DStyle(TEXT("Painter2DStyle"));
	return Painter2DStyle;
}

void FPainter2DStyle::Initialize()
{
	//Icon size
	const FVector2D Icon16x16(16.0f, 16.0f);
	const FVector2D Icon64x64(64.0f, 64.0f);

	if (StyleSet.IsValid())
	{
		return;
	}

	StyleSet = MakeShareable(new FSlateStyleSet(GetStyleSetName()));

	//Asset
	StyleSet->Set("ClassIcon.Painter2DAsset", new IMAGE_PLUGIN_BRUSH(TEXT("Icons/SlateWidgetStyleAsset_16x"), Icon16x16));
	StyleSet->Set("ClassThumbnail.Painter2DAsset", new IMAGE_PLUGIN_BRUSH(TEXT("Icons/SlateWidgetStyleAsset_64x"), Icon64x64));

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
}

#undef IMAGE_PLUGIN_BRUSH

void FPainter2DStyle::Shutdown()
{
	if (StyleSet.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet.Get());
		ensure(StyleSet.IsUnique());
		StyleSet.Reset();
	}
}