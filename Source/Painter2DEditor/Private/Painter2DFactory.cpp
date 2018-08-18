// Fill out your copyright notice in the Description page of Project Settings.
#include "Painter2DFactory.h"
#include "Painter2DAsset.h"

UPainter2DFactory::UPainter2DFactory()
{
	bCreateNew = 1;
	SupportedClass = UPainter2DAsset::StaticClass();
}

UObject* UPainter2DFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	UPainter2DAsset* NewAsset = NewObject<UPainter2DAsset>(InParent, Class, Name, Flags | RF_Transactional);

	NewAsset->InitializeCanvas(512, 512);
	
	return NewAsset;
}

