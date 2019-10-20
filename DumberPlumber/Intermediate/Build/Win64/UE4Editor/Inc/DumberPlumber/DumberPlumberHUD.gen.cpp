// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DumberPlumber/DumberPlumberHUD.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDumberPlumberHUD() {}
// Cross Module References
	DUMBERPLUMBER_API UClass* Z_Construct_UClass_ADumberPlumberHUD_NoRegister();
	DUMBERPLUMBER_API UClass* Z_Construct_UClass_ADumberPlumberHUD();
	ENGINE_API UClass* Z_Construct_UClass_AHUD();
	UPackage* Z_Construct_UPackage__Script_DumberPlumber();
// End Cross Module References
	void ADumberPlumberHUD::StaticRegisterNativesADumberPlumberHUD()
	{
	}
	UClass* Z_Construct_UClass_ADumberPlumberHUD_NoRegister()
	{
		return ADumberPlumberHUD::StaticClass();
	}
	struct Z_Construct_UClass_ADumberPlumberHUD_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ADumberPlumberHUD_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AHUD,
		(UObject* (*)())Z_Construct_UPackage__Script_DumberPlumber,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADumberPlumberHUD_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Rendering Actor Input Replication" },
		{ "IncludePath", "DumberPlumberHUD.h" },
		{ "ModuleRelativePath", "DumberPlumberHUD.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ADumberPlumberHUD_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADumberPlumberHUD>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ADumberPlumberHUD_Statics::ClassParams = {
		&ADumberPlumberHUD::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008002ACu,
		METADATA_PARAMS(Z_Construct_UClass_ADumberPlumberHUD_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_ADumberPlumberHUD_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ADumberPlumberHUD()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ADumberPlumberHUD_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ADumberPlumberHUD, 3721089948);
	template<> DUMBERPLUMBER_API UClass* StaticClass<ADumberPlumberHUD>()
	{
		return ADumberPlumberHUD::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ADumberPlumberHUD(Z_Construct_UClass_ADumberPlumberHUD, &ADumberPlumberHUD::StaticClass, TEXT("/Script/DumberPlumber"), TEXT("ADumberPlumberHUD"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ADumberPlumberHUD);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
