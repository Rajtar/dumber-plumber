// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef DUMBERPLUMBER_DumberPlumberCharacter_generated_h
#error "DumberPlumberCharacter.generated.h already included, missing '#pragma once' in DumberPlumberCharacter.h"
#endif
#define DUMBERPLUMBER_DumberPlumberCharacter_generated_h

#define DumberPlumber_Source_DumberPlumber_DumberPlumberCharacter_h_14_RPC_WRAPPERS
#define DumberPlumber_Source_DumberPlumber_DumberPlumberCharacter_h_14_RPC_WRAPPERS_NO_PURE_DECLS
#define DumberPlumber_Source_DumberPlumber_DumberPlumberCharacter_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesADumberPlumberCharacter(); \
	friend struct Z_Construct_UClass_ADumberPlumberCharacter_Statics; \
public: \
	DECLARE_CLASS(ADumberPlumberCharacter, ACharacter, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/DumberPlumber"), NO_API) \
	DECLARE_SERIALIZER(ADumberPlumberCharacter)


#define DumberPlumber_Source_DumberPlumber_DumberPlumberCharacter_h_14_INCLASS \
private: \
	static void StaticRegisterNativesADumberPlumberCharacter(); \
	friend struct Z_Construct_UClass_ADumberPlumberCharacter_Statics; \
public: \
	DECLARE_CLASS(ADumberPlumberCharacter, ACharacter, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/DumberPlumber"), NO_API) \
	DECLARE_SERIALIZER(ADumberPlumberCharacter)


#define DumberPlumber_Source_DumberPlumber_DumberPlumberCharacter_h_14_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ADumberPlumberCharacter(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ADumberPlumberCharacter) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ADumberPlumberCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ADumberPlumberCharacter); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ADumberPlumberCharacter(ADumberPlumberCharacter&&); \
	NO_API ADumberPlumberCharacter(const ADumberPlumberCharacter&); \
public:


#define DumberPlumber_Source_DumberPlumber_DumberPlumberCharacter_h_14_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ADumberPlumberCharacter(ADumberPlumberCharacter&&); \
	NO_API ADumberPlumberCharacter(const ADumberPlumberCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ADumberPlumberCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ADumberPlumberCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ADumberPlumberCharacter)


#define DumberPlumber_Source_DumberPlumber_DumberPlumberCharacter_h_14_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__Mesh1P() { return STRUCT_OFFSET(ADumberPlumberCharacter, Mesh1P); } \
	FORCEINLINE static uint32 __PPO__FP_Gun() { return STRUCT_OFFSET(ADumberPlumberCharacter, FP_Gun); } \
	FORCEINLINE static uint32 __PPO__FP_MuzzleLocation() { return STRUCT_OFFSET(ADumberPlumberCharacter, FP_MuzzleLocation); } \
	FORCEINLINE static uint32 __PPO__VR_Gun() { return STRUCT_OFFSET(ADumberPlumberCharacter, VR_Gun); } \
	FORCEINLINE static uint32 __PPO__VR_MuzzleLocation() { return STRUCT_OFFSET(ADumberPlumberCharacter, VR_MuzzleLocation); } \
	FORCEINLINE static uint32 __PPO__FirstPersonCameraComponent() { return STRUCT_OFFSET(ADumberPlumberCharacter, FirstPersonCameraComponent); } \
	FORCEINLINE static uint32 __PPO__R_MotionController() { return STRUCT_OFFSET(ADumberPlumberCharacter, R_MotionController); } \
	FORCEINLINE static uint32 __PPO__L_MotionController() { return STRUCT_OFFSET(ADumberPlumberCharacter, L_MotionController); }


#define DumberPlumber_Source_DumberPlumber_DumberPlumberCharacter_h_11_PROLOG
#define DumberPlumber_Source_DumberPlumber_DumberPlumberCharacter_h_14_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DumberPlumber_Source_DumberPlumber_DumberPlumberCharacter_h_14_PRIVATE_PROPERTY_OFFSET \
	DumberPlumber_Source_DumberPlumber_DumberPlumberCharacter_h_14_RPC_WRAPPERS \
	DumberPlumber_Source_DumberPlumber_DumberPlumberCharacter_h_14_INCLASS \
	DumberPlumber_Source_DumberPlumber_DumberPlumberCharacter_h_14_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define DumberPlumber_Source_DumberPlumber_DumberPlumberCharacter_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DumberPlumber_Source_DumberPlumber_DumberPlumberCharacter_h_14_PRIVATE_PROPERTY_OFFSET \
	DumberPlumber_Source_DumberPlumber_DumberPlumberCharacter_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	DumberPlumber_Source_DumberPlumber_DumberPlumberCharacter_h_14_INCLASS_NO_PURE_DECLS \
	DumberPlumber_Source_DumberPlumber_DumberPlumberCharacter_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> DUMBERPLUMBER_API UClass* StaticClass<class ADumberPlumberCharacter>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID DumberPlumber_Source_DumberPlumber_DumberPlumberCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
