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

// Called to bind functionality to input
void APuzzleReader::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    //Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//MY STUFF

TSubclassOf<AActor> APuzzleReader::GetBrickClass(const FString& BrickType)
{
    if (BrickType == TEXT("BB"))
    {
        return BrickBorder;
    }
    else if (BrickType == TEXT("E"))
    {
        return BrickBackBoard;
    }
    else if (BrickType == TEXT("BL"))
    {
        return BrickBlocking;
    }
    else if (BrickType == TEXT("CLO"))
    {
        return BrickCLOrange;
    }
    else if (BrickType == TEXT("GO"))
    {
        return BrickGoalOrange;
    }

    return nullptr;
}

TArray<AActor*> APuzzleReader::ReadPuzzle(FString id, int32& OutRows, int32& OutColumns)
{
    TArray<AActor*> PuzzleActors;

    // Define the path to the JSON file
    FString FilePath = FPaths::ProjectContentDir() / TEXT("Data/PuzzleData.json");
    FString JsonString;

    // Load the JSON file to a string
    if (FFileHelper::LoadFileToString(JsonString, *FilePath))
    {
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
                            for (const FPuzzle& Puzzle : Biome.Puzzles)
                            {
                                if (Puzzle.Id == PuzzleId)
                                {
                                    // Set the output rows and columns
                                    OutRows = Puzzle.Grid.Num();
                                    OutColumns = (Puzzle.Grid.Num() > 0) ? Puzzle.Grid[0].Num() : 0;

                                    // Process the puzzle grid
                                    for (int32 RowIndex = 0; RowIndex < Puzzle.Grid.Num(); ++RowIndex)
                                    {
                                        const TArray<FString>& GridRow = Puzzle.Grid[RowIndex];
                                        for (int32 ColIndex = 0; ColIndex < GridRow.Num(); ++ColIndex)
                                        {
                                            FString BrickType = GridRow[ColIndex];
                                            TSubclassOf<AActor> BrickClass = GetBrickClass(BrickType);

                                            if (BrickClass)
                                            {
                                                // Spawn an actor and add it to the array
                                                AActor* NewBrick = GetWorld()->SpawnActor<AActor>(BrickClass, FVector::ZeroVector, FRotator::ZeroRotator);
                                                if (NewBrick)
                                                {
                                                    PuzzleActors.Add(NewBrick);
                                                }
                                            }
                                        }
                                    }

                                    return PuzzleActors;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // Return empty array if the puzzle is not found or cannot be loaded
    return PuzzleActors;
}

