/*
    Author: baihan 
    class purpose: Remember if Mind 
*/

#pragma once

#include "Structure/Memory.h"
#include "Remember.generated.h"

UINTERFACE()
class MINDCORE_API URemember : public UInterface
{
    GENERATED_BODY()
};

class MINDCORE_API IRemember
{
    GENERATED_BODY()

public:
    void Store();
    void Recall(int memoryID);
    void Share(int memoryID);
    void Accept(int memoryID);
};