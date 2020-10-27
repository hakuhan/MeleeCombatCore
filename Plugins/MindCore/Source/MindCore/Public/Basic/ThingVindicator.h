/*
    Author: baihan 
    class purpose: Thing ID creater and mange all ting ID 
*/

#include "ThingVindicator.generated.h"

UCLASS()
class MINDCORE_API UThingVindicator : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    TArray<FString> m_ThingTypes;

    UPROPERTY()
    TArray<FString> m_ThingGamingAddTypes;

    UThingVindicator();

    bool RegistThingType(FString type);

    bool CheckThingType(FString type);
};