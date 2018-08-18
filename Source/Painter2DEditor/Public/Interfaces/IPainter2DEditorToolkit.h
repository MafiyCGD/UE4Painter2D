#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"

class UPainter2DAsset;
/**
 * Interface for texture editor tool kits.
 */
class IPainter2DEditorToolkit
	: public FAssetEditorToolkit
{
public:
	virtual TWeakObjectPtr<UPainter2DAsset> GetPainter2DAsset() = 0;
};