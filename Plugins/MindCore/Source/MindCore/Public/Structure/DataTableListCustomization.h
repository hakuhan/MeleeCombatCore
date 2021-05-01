#pragma once

#include "CoreMinimal.h"
#include "Editor/PropertyEditor/Public/IPropertyTypeCustomization.h"
#include "DataTableRows.h"

class FDataTableListCustomization : public IPropertyTypeCustomization
{
public:
    static TSharedRef<IPropertyTypeCustomization> MakeInstance()
    {
        return MakeShareable( new FDataTableListCustomization );
    }

    /** IPropertyTypeCustomization interface */
	virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

};