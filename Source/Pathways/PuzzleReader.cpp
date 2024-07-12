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


TArray<AActor*> APuzzleReader::ReadPuzzle(FString id, int32& OutRows, int32& OutColumns, FString& Test)
{
    TArray<AActor*> PuzzleActors;

    // Define the path to the JSON file
    FString FilePath = FPaths::ProjectContentDir() / TEXT("PathWays/Data/PuzzleData.json");
    FString JsonString;

    // Load the JSON file to a string
    if (FFileHelper::LoadFileToString(JsonString, *FilePath))
    {
        /////Test = JsonString;

        // Parse the JSON string to a JSON object
        TSharedPtr<FJsonObject> JsonObject;
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

        if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
        {

            FBiomesData BiomesData;
            if (FJsonObjectConverter::JsonObjectToUStruct(JsonObject.ToSharedRef(), &BiomesData, 0, 0))
            {
                Test = TEXT("a");

                // Extract the biome name and puzzle ID from the given ID string
                FString BiomeName;
                FString PuzzleIdStr;
                if (id.Split("_", &BiomeName, &PuzzleIdStr))
                {
                    Test = PuzzleIdStr;

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
                                            APuzzleReader temp;
                                            TSubclassOf<AActor> BrickClass = temp.GetBrickClass(BrickType);

                                            if (BrickClass)
                                            {
                                                // Just create instances of the actors and add to the array
                                                AActor* NewBrick = NewObject<AActor>(GetTransientPackage(), BrickClass);
                                                PuzzleActors.Add(NewBrick);
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

    // Return empty array if the puzzle is not found
    return PuzzleActors;
}

