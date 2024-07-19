// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzleReader.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "JsonObjectConverter.h"

// Sets default values
APuzzleReader::APuzzleReader()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APuzzleReader::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void APuzzleReader::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

//MY STUFF

FString APuzzleReader::GetBrickClass(const FString& BrickType)
{
    if (BrickType == TEXT("EE"))
    {
        return TEXT("BP_Brick_BackBord");
    }
    else if (BrickType == TEXT("BL"))
    {
        return TEXT("BP_Brick_Blocking");
    }
    else if (BrickType == TEXT("BB"))
    {
        return TEXT("BP_Brick_Border");
    }
    else if (BrickType == TEXT("CO"))
    {
        return TEXT("BP_Brick_CL_Orange");
    }
    else if (BrickType == TEXT("CG"))
    {
        return TEXT("BP_Brick_CL_Green");
    }
    else if (BrickType == TEXT("GO"))
    {
        return TEXT("BP_Brick_Goal_Orange");
    }
    else if (BrickType == TEXT("GG"))
    {
        return TEXT("BP_Brick_Goal_Green");
    }

    return TEXT("BrickFailed");
}

TArray<FString> APuzzleReader::ReadPuzzle(FString id, int32& OutRows, int32& OutColumns)
{
    TArray<FString> PuzzleStrings;
    // Define the path to the JSON file
    FString FilePath = FPaths::ProjectContentDir() / TEXT("PathWays/Data/PuzzleData.json");
    FString JsonString;

    // Load the JSON file to a string
    if (FFileHelper::LoadFileToString(JsonString, *FilePath))
    {
        // Log the loaded JSON string (for debugging)
        UE_LOG(LogTemp, Warning, TEXT("Loaded JSON content: %s"), *JsonString);

        // Parse the JSON string to a JSON object
        TSharedPtr<FJsonObject> JsonObject;
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

        if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
        {
            FBiomesData BiomesData;
            if (FJsonObjectConverter::JsonObjectToUStruct(JsonObject.ToSharedRef(), &BiomesData, 0, 0))
            {
                // Extract the biome name and puzzle ID from the given ID string
                FString BiomeName;
                FString PuzzleIdStr;
                if (id.Split("_", &BiomeName, &PuzzleIdStr))
                {
                    int32 PuzzleId = FCString::Atoi(*PuzzleIdStr);

                    // Find the matching biome
                    for (const FBiome& Biome : BiomesData.Biomes)
                    {
                        if (Biome.Name == BiomeName)
                        {
                            // Find the matching puzzle in the biome
                            for (const FGamePuzzle& Puzzle : Biome.Puzzles)
                            {
                                if (Puzzle.Id == PuzzleId)
                                {
                                    // Set the output rows and columns
                                    OutRows = Puzzle.Rows;
                                    OutColumns = Puzzle.Columns;

                                    // Create actors or process the puzzle data as needed
                                    for (int32 RowIndex = 0; RowIndex < Puzzle.Grid.Num(); ++RowIndex)
                                    {
                                        const FGridRow& GridRow = Puzzle.Grid[RowIndex];
                                        for (int32 ColIndex = 0; ColIndex < GridRow.Row.Num(); ++ColIndex)
                                        {
                                            FString BrickType = GridRow.Row[ColIndex];
                                            FString BrickClass = GetBrickClass(BrickType);
                                            PuzzleStrings.Add(BrickClass);
                                        }
                                    }

                                    return PuzzleStrings;
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                // Log the error if JSON to UStruct conversion fails
                UE_LOG(LogTemp, Error, TEXT("Failed to deserialize JSON"));
            }
        }
        else
        {
            // Log an error if JSON deserialization fails
            UE_LOG(LogTemp, Error, TEXT("Failed to deserialize JSON"));
        }
    }
    else
    {
        // Log an error if file loading fails
        UE_LOG(LogTemp, Error, TEXT("Failed to load JSON file: %s"), *FilePath);
    }

    // Return empty array if the puzzle is not found or there was an error
    return PuzzleStrings;
}