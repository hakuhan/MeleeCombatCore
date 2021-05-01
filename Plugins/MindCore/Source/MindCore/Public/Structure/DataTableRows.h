#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DataTableRows.generated.h"

USTRUCT(BlueprintType)
struct MINDCORE_API FDataTableRows
{
    GENERATED_USTRUCT_BODY()

    FDataTableRows()
    : DataTable(nullptr)
    , Rows(TArray<FName>())
    {

    }

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DataTableRows)
    const UDataTable* DataTable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DataTableRows)
    TArray<FName> Rows;

    bool IsNull() const
    {
        return DataTable == nullptr && Rows.Num() == 0;
    }

    template<class T>
    bool GetRows(const TCHAR* ContextString, TArray<T*>& outRows) const
    {
        bool result = false;
        if (DataTable)
        {
            outRows.Empty();

            for (FName rowName : Rows)
            {
                outRows.Add(DataTable->FindRow<T>(rowName, ContextString));
            }

            result = outRows.Num() > 0;
        }

        return result;
    }

    template<class T>
    bool GetRows(const FString& ContextString, TArray<T*>& outRows) const
    {
        return GetRows<T>(*ContextString, outRows);
    }

    bool operator==(FDataTableRows const& Other) const
    {
        return DataTable == Other.DataTable && Rows == Other.Rows;
    }

    bool operator != (FDataTableRows const& Other) const
    {
        return DataTable != Other.DataTable || Rows != Other.Rows;
    }

	void PostSerialize(const FArchive& Ar)
    {
        if (Ar.IsSaving() && !IsNull() && DataTable)
        {
            // Note which row we are pointing to for later searching
            for (int i = 0; i < Rows.Num(); ++i)
                Ar.MarkSearchableName(DataTable, Rows[i]);
        }
    }
};