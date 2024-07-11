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

TArray<AActor*> APuzzleReader::ReadPuzzle(FString id)
{
	TArray<AActor*> PuzzleActors;

	// Define the path to the JSON file
	FString FilePath = FPaths::ProjectContentDir() / TEXT("Pathways/Content/PathWays/Data/PuzzleData.json");
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
                            for (const FGamePuzzle& Puzzle : Biome.Puzzles)
                            {
                                if (Puzzle.Id == PuzzleId)
                                {
                                    // Create actors or process the puzzle data as needed
                                    // For example, you could create puzzle pieces here and add them to PuzzleActors
                                    // (Your code to create and return puzzle actors)

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

