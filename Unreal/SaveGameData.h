#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameData.generated.h"

UCLASS()
class USaveGameData : public USaveGame
{
    GENERATED_BODY()
public:
    UPROPERTY()
    int32 integer_one;

    UPROPERTY()
    int32 integer_two;

    UPROPERTY()
    int32 integer_three;

    UPROPERTY()
    int32 integer_four;

    UPROPERTY()
    float float_one;

    UPROPERTY()
    float float_two;

    UPROPERTY()
    float float_three;

    UPROPERTY()
    FVector vector_one;

    UPROPERTY()
    FVector vector_two;

    static USaveGameData* Current;

    static void LoadFromFile(const FString& Path);
    static void SaveToFile(const FString& Path);
    static bool TryLoadFromArgs();
};
