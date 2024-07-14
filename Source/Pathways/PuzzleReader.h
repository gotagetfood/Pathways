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

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> Row;
};

USTRUCT(BlueprintType)
struct FGamePuzzle
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Id;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Rows;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Columns;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FGridRow> Grid;
};

USTRUCT(BlueprintType)
struct FBiome
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FGamePuzzle> Puzzles;
};

USTRUCT(BlueprintType)
struct FBiomesData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FBiome> Biomes;
};

UCLASS()
class PATHWAYS_API APuzzleReader : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    APuzzleReader();

    UFUNCTION(BlueprintCallable, Category = "Puzzle")
    virtual TArray<FString> ReadPuzzle(FString id, int32& OutRows, int32& OutColumns);

private:
    FString GetBrickClass(const FString& BrickType);

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
};