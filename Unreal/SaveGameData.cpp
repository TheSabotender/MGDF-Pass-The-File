#include "SaveGameData.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Misc/CommandLine.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

USaveGameData* USaveGameData::Current = nullptr;

void USaveGameData::LoadFromFile(const FString& Path)
{
    FString Content;
    if (FFileHelper::LoadFileToString(Content, *Path))
    {
        TSharedPtr<FJsonObject> JsonObject;
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Content);
        if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
        {
            USaveGameData* Data = NewObject<USaveGameData>();
            Data->integer_one = JsonObject->GetIntegerField(TEXT("integer_one"));
            Data->integer_two = JsonObject->GetIntegerField(TEXT("integer_two"));
            Data->integer_three = JsonObject->GetIntegerField(TEXT("integer_three"));
            Data->integer_four = JsonObject->GetIntegerField(TEXT("integer_four"));
            Data->float_one = JsonObject->GetNumberField(TEXT("float_one"));
            Data->float_two = JsonObject->GetNumberField(TEXT("float_two"));
            Data->float_three = JsonObject->GetNumberField(TEXT("float_three"));

            const TSharedPtr<FJsonObject>* VecObj;
            if (JsonObject->TryGetObjectField(TEXT("vector_one"), VecObj))
            {
                Data->vector_one.X = (*VecObj)->GetNumberField(TEXT("x"));
                Data->vector_one.Y = (*VecObj)->GetNumberField(TEXT("y"));
                Data->vector_one.Z = (*VecObj)->GetNumberField(TEXT("z"));
            }
            if (JsonObject->TryGetObjectField(TEXT("vector_two"), VecObj))
            {
                Data->vector_two.X = (*VecObj)->GetNumberField(TEXT("x"));
                Data->vector_two.Y = (*VecObj)->GetNumberField(TEXT("y"));
                Data->vector_two.Z = (*VecObj)->GetNumberField(TEXT("z"));
            }
            Current = Data;
        }
    }
}

void USaveGameData::SaveToFile(const FString& Path)
{
    if (!Current)
    {
        return;
    }

    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
    JsonObject->SetNumberField(TEXT("integer_one"), Current->integer_one);
    JsonObject->SetNumberField(TEXT("integer_two"), Current->integer_two);
    JsonObject->SetNumberField(TEXT("integer_three"), Current->integer_three);
    JsonObject->SetNumberField(TEXT("integer_four"), Current->integer_four);
    JsonObject->SetNumberField(TEXT("float_one"), Current->float_one);
    JsonObject->SetNumberField(TEXT("float_two"), Current->float_two);
    JsonObject->SetNumberField(TEXT("float_three"), Current->float_three);

    TSharedPtr<FJsonObject> VecObj = MakeShareable(new FJsonObject);
    VecObj->SetNumberField(TEXT("x"), Current->vector_one.X);
    VecObj->SetNumberField(TEXT("y"), Current->vector_one.Y);
    VecObj->SetNumberField(TEXT("z"), Current->vector_one.Z);
    JsonObject->SetObjectField(TEXT("vector_one"), VecObj);

    VecObj = MakeShareable(new FJsonObject);
    VecObj->SetNumberField(TEXT("x"), Current->vector_two.X);
    VecObj->SetNumberField(TEXT("y"), Current->vector_two.Y);
    VecObj->SetNumberField(TEXT("z"), Current->vector_two.Z);
    JsonObject->SetObjectField(TEXT("vector_two"), VecObj);

    FString Output;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Output);
    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
    FFileHelper::SaveStringToFile(Output, *Path);
}

bool USaveGameData::TryLoadFromArgs()
{
    TArray<FString> Args;
    FString(FCommandLine::Get()).ParseIntoArrayWS(Args);
    for (int32 i = 0; i < Args.Num() - 1; ++i)
    {
        if (Args[i].Equals(TEXT("-load"), ESearchCase::IgnoreCase))
        {
            FString FilePath = Args[i + 1];
            if (FPaths::GetExtension(FilePath).Equals(TEXT("mgdf"), ESearchCase::IgnoreCase) && FPaths::FileExists(FilePath))
            {
                LoadFromFile(FilePath);
                return true;
            }
            break;
        }
    }
    return false;
}
