// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DumberPlumber/DumberPlumberGameMode.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDumberPlumberGameMode() {}
// Cross Module References
	DUMBERPLUMBER_API UClass* Z_Construct_UClass_ADumberPlumberGameMode_NoRegister();
	DUMBERPLUMBER_API UClass* Z_Construct_UClass_ADumberPlumberGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_DumberPlumber();
// End Cross Module References
	void ADumberPlumberGameMode::StaticRegisterNativesADumberPlumberGameMode()
	{
	}
	UClass* Z_Construct_UClass_ADumberPlumberGameMode_NoRegister()
	{
		return ADumberPlumberGameMode::StaticClass();
	}
	struct Z_Construct_UClass_ADumberPlumberGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ADumberPlumberGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_DumberPlumber,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADumberPlumberGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "DumberPlumberGameMode.h" },
		{ "ModuleRelativePath", "DumberPlumberGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ADumberPlumberGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADumberPlumberGameMode>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ADumberPlumberGameMode_Statics::ClassParams = {
		&ADumberPlumberGameMode::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008802A8u,
		METADATA_PARAMS(Z_Construct_UClass_ADumberPlumberGameMode_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_ADumberPlumberGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ADumberPlumberGameMode()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ADumberPlumberGameMode_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ADumberPlumberGameMode, 2935541548);
	template<> DUMBERPLUMBER_API UClass* StaticClass<ADumberPlumberGameMode>()
	{
		return ADumberPlumberGameMode::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ADumberPlumberGameMode(Z_Construct_UClass_ADumberPlumberGameMode, &ADumberPlumberGameMode::StaticClass, TEXT("/Script/DumberPlumber"), TEXT("ADumberPlumberGameMode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ADumberPlumberGameMode);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
