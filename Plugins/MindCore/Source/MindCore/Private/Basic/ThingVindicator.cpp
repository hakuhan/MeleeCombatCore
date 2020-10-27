#include "Basic/ThingVindicator.h"

UThingVindicator::UThingVindicator()
{
}

bool UThingVindicator::RegistThingType(FString type)
{
    bool result = false;

    if (CheckThingType(type))
    {
        result = true;

        m_ThingGamingAddTypes.Add(type);
    }

    return result;
}

bool UThingVindicator::CheckThingType(FString type)
{
    return !m_ThingTypes.Contains(type) && m_ThingGamingAddTypes.Contains(type);
}