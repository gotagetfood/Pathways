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
    //BASE BRICKS
    if (BrickType == TEXT("BB"))
    {
        return TEXT("Backboard");
    }
    else if (BrickType == TEXT("BL"))
    {
        return TEXT("Blocking");
    }
    else if (BrickType == TEXT("BO"))
    {
        return TEXT("Border");
    }
    else if (BrickType == TEXT("BI"))
    {
        return TEXT("Ice");
    }
    else if (BrickType == TEXT("BC"))
    {
        return TEXT("Cross");
    }//color lines
    else if (BrickType == TEXT("CO"))
    {
        return TEXT("CL_Orange");
    }
    else if (BrickType == TEXT("CG"))
    {
        return TEXT("CL_Green");
    }
    else if (BrickType == TEXT("CB"))
    {
        return TEXT("CL_Blue");
    }
    else if (BrickType == TEXT("CL"))
    {
        return TEXT("CL_Light_Blue");
    }
    else if (BrickType == TEXT("CP"))
    {
        return TEXT("CL_Purple");
    }
    else if (BrickType == TEXT("CI"))
    {
        return TEXT("CL_Pink");
    }
    else if (BrickType == TEXT("CY"))
    {
        return TEXT("CL_Yellow");
    }
    else if (BrickType == TEXT("CR"))
    {
        return TEXT("CL_Red");
    }
    else if (BrickType == TEXT("CW"))
    {
        return TEXT("CL_Brown");
    }
    else if (BrickType == TEXT("CE"))
    {
        return TEXT("CL_Dark_Green");
    }
    else if (BrickType == TEXT("CA"))
    {
        return TEXT("CL_Cyan");
    }
    else if (BrickType == TEXT("CD"))
    {
        return TEXT("CL_Dark_Red");
    }//goals
    else if (BrickType == TEXT("GO"))
    {
        return TEXT("GO_Orange");
    }
    else if (BrickType == TEXT("GG"))
    {
        return TEXT("GO_Green");
    }
    else if (BrickType == TEXT("GB"))
    {
        return TEXT("GO_Blue");
    }
    else if (BrickType == TEXT("GL"))
    {
        return TEXT("GO_Light_Blue");
    }
    else if (BrickType == TEXT("GP"))
    {
        return TEXT("GO_Purple");
    }
    else if (BrickType == TEXT("GI"))
    {
        return TEXT("GO_Pink");
    }
    else if (BrickType == TEXT("GY"))
    {
        return TEXT("GO_Yellow");
    }
    else if (BrickType == TEXT("GR"))
    {
        return TEXT("GO_Red");
    }
    else if (BrickType == TEXT("GW"))
    {
        return TEXT("GO_Brown");
    }
    else if (BrickType == TEXT("GE"))
    {
        return TEXT("GO_Dark_Green");
    }
    else if (BrickType == TEXT("GA"))
    {
        return TEXT("GO_Cyan");
    }
    else if (BrickType == TEXT("GD"))
    {
        return TEXT("GO_Dark_Red");
    }//line complete
    else if (BrickType == TEXT("LO"))
    {
        return TEXT("LC_Orange");
    }
    else if (BrickType == TEXT("LG"))
    {
        return TEXT("LC_Green");
    }
    else if (BrickType == TEXT("LB"))
    {
        return TEXT("LC_Blue");
    }
    else if (BrickType == TEXT("LL"))
    {
        return TEXT("LC_Light_Blue");
    }
    else if (BrickType == TEXT("LP"))
    {
        return TEXT("LC_Purple");
    }
    else if (BrickType == TEXT("LI"))
    {
        return TEXT("LC_Pink");
    }
    else if (BrickType == TEXT("LY"))
    {
        return TEXT("LC_Yellow");
    }
    else if (BrickType == TEXT("LR"))
    {
        return TEXT("LC_Red");
    }
    else if (BrickType == TEXT("LW"))
    {
        return TEXT("LC_Brown");
    }
    else if (BrickType == TEXT("LE"))
    {
        return TEXT("LC_Dark_Green");
    }
    else if (BrickType == TEXT("LA"))
    {
        return TEXT("LC_Cyan");
    }
    else if (BrickType == TEXT("LD"))
    {
        return TEXT("LC_Dark_Red");
    }//colorless
    else if (BrickType == TEXT("CK"))
    {
        return TEXT("CL_Colorless");
    }
    else if (BrickType == TEXT("GK"))
    {
        return TEXT("GO_Colorless");
    }
    else if (BrickType == TEXT("LK"))
    {
        return TEXT("LC_Colorless");
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