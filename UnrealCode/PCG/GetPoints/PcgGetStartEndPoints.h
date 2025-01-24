// Copyright 2025 Helm Boy Studios . All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "PCGElement.h"
#include "PCGSettings.h"
#include "UObject/Object.h"
#include "PcgUtils.generated.h"

UENUM(BlueprintType)
enum EGetPointMode : uint8
{
	Last,
	First,
	StartAndEnd,
};
/* Boiler plate class for the Graph UI */
UCLASS(BlueprintType, ClassGroup = (Procedural))
class INSERTYOURMODULENAME_API UGetPointContext : public UPCGSettings
{
	GENERATED_BODY()
public:
	UGetPointContext();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
	TEnumAsByte<EGetPointMode> Mode;
	
	//~Begin UObject interface
	virtual void PostLoad() override;
	//~End UObject interface

	//~Begin UPCGSettings interface
#if WITH_EDITOR
	virtual FName GetDefaultNodeName() const override { return "GetStartOrLastPointContext"; }
	virtual FText GetDefaultNodeTitle() const override { return NSLOCTEXT("PCGBaseNodeSettings", "NodeTitle", "Get Start Or Last Point"); }
	virtual FText GetNodeTooltipText() const override { return FText::FromString("Gets the Start or Last point of a point data set"); }
	virtual FLinearColor GetNodeTitleColor() const override { return FLinearColor::Gray; }
	virtual EPCGSettingsType GetType() const override { return EPCGSettingsType::Filter; }
	virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;
	virtual void PostDuplicate(bool bDuplicateForPIE) override;
#endif

	virtual TArray<FPCGPinProperties> InputPinProperties() const override ;
	virtual TArray<FPCGPinProperties> OutputPinProperties() const override;
	
protected:
	// makes a FGetPointElement 
	virtual FPCGElementPtr CreateElement() const override;
};

class FGetPointElement  : public FSimplePCGElement
{
protected:
	// does the actual thing
	virtual bool ExecuteInternal(FPCGContext* Context) const override;
};