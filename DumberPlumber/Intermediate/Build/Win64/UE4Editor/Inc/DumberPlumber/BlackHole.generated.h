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
struct FHitResult;
#ifdef DUMBERPLUMBER_BlackHole_generated_h
#error "BlackHole.generated.h already included, missing '#pragma once' in BlackHole.h"
#endif
#define DUMBERPLUMBER_BlackHole_generated_h

#define DumberPlumber_Source_DumberPlumber_BlackHole_h_15_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execOverlapInnerSphere) \
	{ \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OverlappedComponent); \
		P_GET_OBJECT(AActor,Z_Param_OtherActor); \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComponent); \
		P_GET_PROPERTY(UIntProperty,Z_Param_OtherBodyIndex); \
		P_GET_UBOOL(Z_Param_bFromSweep); \
		P_GET_STRUCT_REF(FHitResult,Z_Param_Out_SweepResult); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->OverlapInnerSphere(Z_Param_OverlappedComponent,Z_Param_OtherActor,Z_Param_OtherComponent,Z_Param_OtherBodyIndex,Z_Param_bFromSweep,Z_Param_Out_SweepResult); \
		P_NATIVE_END; \
	}


#define DumberPlumber_Source_DumberPlumber_BlackHole_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOverlapInnerSphere) \
	{ \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OverlappedComponent); \
		P_GET_OBJECT(AActor,Z_Param_OtherActor); \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComponent); \
		P_GET_PROPERTY(UIntProperty,Z_Param_OtherBodyIndex); \
		P_GET_UBOOL(Z_Param_bFromSweep); \
		P_GET_STRUCT_REF(FHitResult,Z_Param_Out_SweepResult); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->OverlapInnerSphere(Z_Param_OverlappedComponent,Z_Param_OtherActor,Z_Param_OtherComponent,Z_Param_OtherBodyIndex,Z_Param_bFromSweep,Z_Param_Out_SweepResult); \
		P_NATIVE_END; \
	}


#define DumberPlumber_Source_DumberPlumber_BlackHole_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesABlackHole(); \
	friend struct Z_Construct_UClass_ABlackHole_Statics; \
public: \
	DECLARE_CLASS(ABlackHole, AActor, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/DumberPlumber"), NO_API) \
	DECLARE_SERIALIZER(ABlackHole)


#define DumberPlumber_Source_DumberPlumber_BlackHole_h_15_INCLASS \
private: \
	static void StaticRegisterNativesABlackHole(); \
	friend struct Z_Construct_UClass_ABlackHole_Statics; \
public: \
	DECLARE_CLASS(ABlackHole, AActor, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/DumberPlumber"), NO_API) \
	DECLARE_SERIALIZER(ABlackHole)


#define DumberPlumber_Source_DumberPlumber_BlackHole_h_15_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ABlackHole(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ABlackHole) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ABlackHole); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ABlackHole); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ABlackHole(ABlackHole&&); \
	NO_API ABlackHole(const ABlackHole&); \
public:


#define DumberPlumber_Source_DumberPlumber_BlackHole_h_15_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ABlackHole(ABlackHole&&); \
	NO_API ABlackHole(const ABlackHole&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ABlackHole); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ABlackHole); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ABlackHole)


#define DumberPlumber_Source_DumberPlumber_BlackHole_h_15_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__MeshComponent() { return STRUCT_OFFSET(ABlackHole, MeshComponent); } \
	FORCEINLINE static uint32 __PPO__InnerSphereComponent() { return STRUCT_OFFSET(ABlackHole, InnerSphereComponent); } \
	FORCEINLINE static uint32 __PPO__OuterSphereComponent() { return STRUCT_OFFSET(ABlackHole, OuterSphereComponent); }


#define DumberPlumber_Source_DumberPlumber_BlackHole_h_12_PROLOG
#define DumberPlumber_Source_DumberPlumber_BlackHole_h_15_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DumberPlumber_Source_DumberPlumber_BlackHole_h_15_PRIVATE_PROPERTY_OFFSET \
	DumberPlumber_Source_DumberPlumber_BlackHole_h_15_RPC_WRAPPERS \
	DumberPlumber_Source_DumberPlumber_BlackHole_h_15_INCLASS \
	DumberPlumber_Source_DumberPlumber_BlackHole_h_15_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define DumberPlumber_Source_DumberPlumber_BlackHole_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DumberPlumber_Source_DumberPlumber_BlackHole_h_15_PRIVATE_PROPERTY_OFFSET \
	DumberPlumber_Source_DumberPlumber_BlackHole_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	DumberPlumber_Source_DumberPlumber_BlackHole_h_15_INCLASS_NO_PURE_DECLS \
	DumberPlumber_Source_DumberPlumber_BlackHole_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> DUMBERPLUMBER_API UClass* StaticClass<class ABlackHole>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID DumberPlumber_Source_DumberPlumber_BlackHole_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
