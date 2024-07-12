// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PuzzleReader.generated.h"

USTRUCT(BlueprintType)
struct FGridRow
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    TArray<FString> Row;
};

USTRUCT(BlueprintType)
struct FGamePuzzle
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    int32 Id;

    UPROPERTY(BlueprintReadWrite)
    TArray<FGridRow> Grid;
};

USTRUCT(BlueprintType)
struct FBiome
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FString Name;

    UPROPERTY(BlueprintReadWrite)
    TArray<FGamePuzzle> Puzzles;
};

USTRUCT(BlueprintType)
struct FBiomesData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    TArray<FBiome> Biomes;
};

UCLASS()
class PATHWAYS_API APuzzleReader : public APawn
{
    GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    APuzzleReader();

    UFUNCTION(BlueprintCallable, Category = "PuzzleReader")
    virtual TArray<AActor*> ReadPuzzle(FString id);

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};