// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Painter2DModule.h"
#include "Core.h"
#include "ModuleManager.h"
#include "IPluginManager.h"

#define LOCTEXT_NAMESPACE "FPainter2DModule"

void FPainter2DModule::StartupModule()
{
}

void FPainter2DModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FPainter2DModule, Painter2D)