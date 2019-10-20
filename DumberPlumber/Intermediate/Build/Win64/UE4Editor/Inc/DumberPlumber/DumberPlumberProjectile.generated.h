// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UPrimitiveComponent;
class AActor;
struct FVector;
struct FHitResult;
#ifdef DUMBERPLUMBER_DumberPlumberProjectile_generated_h
#error "DumberPlumberProjectile.generated.h already included, missing '#pragma once' in DumberPlumberProjectile.h"
#endif
#define DUMBERPLUMBER_DumberPlumberProjectile_generated_h

#define DumberPlumber_Source_DumberPlumber_DumberPlumberProjectile_h_12_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execOnHit) \
	{ \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_HitComp); \
		P_GET_OBJECT(AActor,Z_Param_OtherActor); \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComp); \
		P_GET_STRUCT(FVector,Z_Param_NormalImpulse); \
		P_GET_STRUCT_REF(FHitResult,Z_Param_Out_Hit); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->OnHit(Z_Param_HitComp,Z_Param_OtherActor,Z_Param_OtherComp,Z_Param_NormalImpulse,Z_Param_Out_Hit); \
		P_NATIVE_END; \
	}


#define DumberPlumber_Source_DumberPlumber_DumberPlumberProjectile_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnHit) \
	{ \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_HitComp); \
		P_GET_OBJECT(AActor,Z_Param_OtherActor); \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComp); \
		P_GET_STRUCT(FVector,Z_Param_NormalImpulse); \
		P_GET_STRUCT_REF(FHitResult,Z_Param_Out_Hit); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->OnHit(Z_Param_HitComp,Z_Param_OtherActor,Z_Param_OtherComp,Z_Param_NormalImpulse,Z_Param_Out_Hit); \
		P_NATIVE_END; \
	}


#define DumberPlumber_Source_DumberPlumber_DumberPlumberProjectile_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesADumberPlumberProjectile(); \
	friend struct Z_Construct_UClass_ADumberPlumberProjectile_Statics; \
public: \
	DECLARE_CLASS(ADumberPlumberProjectile, AActor, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/DumberPlumber"), NO_API) \
	DECLARE_SERIALIZER(ADumberPlumberProjectile) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define DumberPlumber_Source_DumberPlumber_DumberPlumberProjectile_h_12_INCLASS \
private: \
	static void StaticRegisterNativesADumberPlumberProjectile(); \
	friend struct Z_Construct_UClass_ADumberPlumberProjectile_Statics; \
public: \
	DECLARE_CLASS(ADumberPlumberProjectile, AActor, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/DumberPlumber"), NO_API) \
	DECLARE_SERIALIZER(ADumberPlumberProjectile) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define DumberPlumber_Source_DumberPlumber_DumberPlumberProjectile_h_12_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ADumberPlumberProjectile(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ADumberPlumberProjectile) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ADumberPlumberProjectile); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ADumberPlumberProjectile); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ADumberPlumberProjectile(ADumberPlumberProjectile&&); \
	NO_API ADumberPlumberProjectile(const ADumberPlumberProjectile&); \
public:


#define DumberPlumber_Source_DumberPlumber_DumberPlumberProjectile_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ADumberPlumberProjectile(ADumberPlumberProjectile&&); \
	NO_API ADumberPlumberProjectile(const ADumberPlumberProjectile&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ADumberPlumberProjectile); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ADumberPlumberProjectile); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ADumberPlumberProjectile)


#define DumberPlumber_Source_DumberPlumber_DumberPlumberProjectile_h_12_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__CollisionComp() { return STRUCT_OFFSET(ADumberPlumberProjectile, CollisionComp); } \
	FORCEINLINE static uint32 __PPO__ProjectileMovement() { return STRUCT_OFFSET(ADumberPlumberProjectile, ProjectileMovement); }


#define DumberPlumber_Source_DumberPlumber_DumberPlumberProjectile_h_9_PROLOG
#define DumberPlumber_Source_DumberPlumber_DumberPlumberProjectile_h_12_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DumberPlumber_Source_DumberPlumber_DumberPlumberProjectile_h_12_PRIVATE_PROPERTY_OFFSET \
	DumberPlumber_Source_DumberPlumber_DumberPlumberProjectile_h_12_RPC_WRAPPERS \
	DumberPlumber_Source_DumberPlumber_DumberPlumberProjectile_h_12_INCLASS \
	DumberPlumber_Source_DumberPlumber_DumberPlumberProjectile_h_12_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define DumberPlumber_Source_DumberPlumber_DumberPlumberProjectile_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DumberPlumber_Source_DumberPlumber_DumberPlumberProjectile_h_12_PRIVATE_PROPERTY_OFFSET \
	DumberPlumber_Source_DumberPlumber_DumberPlumberProjectile_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	DumberPlumber_Source_DumberPlumber_DumberPlumberProjectile_h_12_INCLASS_NO_PURE_DECLS \
	DumberPlumber_Source_DumberPlumber_DumberPlumberProjectile_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> DUMBERPLUMBER_API UClass* StaticClass<class ADumberPlumberProjectile>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID DumberPlumber_Source_DumberPlumber_DumberPlumberProjectile_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
