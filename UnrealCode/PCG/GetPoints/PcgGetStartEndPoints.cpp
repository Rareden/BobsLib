// Copyright 2025 Helm Boy Studios . All rights reserved


#include "PcgGetStartEndPoints.h"
#include "PCGContext.h"
#include "PCGPin.h"
#include "Data/PCGPointData.h"

UGetPointContext::UGetPointContext(): Mode(EGetPointMode::Last)
{
}

void UGetPointContext::PostLoad()
{
	Super::PostLoad();
}
#if WITH_EDITOR
void UGetPointContext::PostDuplicate(EDuplicateMode::Type DuplicateMode)
{
	
}

void UGetPointContext::PostDuplicate(bool bDuplicateForPIE)
{
	Super::PostDuplicate(bDuplicateForPIE);
}
#endif
TArray<FPCGPinProperties> UGetPointContext::InputPinProperties() const
{
	TArray<FPCGPinProperties> PinProperties;
	PinProperties.Emplace(TEXT("In"), EPCGDataType::Point);
	return PinProperties;
	
}

TArray<FPCGPinProperties> UGetPointContext::OutputPinProperties() const
{
	TArray<FPCGPinProperties> PinProperties;
	PinProperties.Emplace(TEXT("Out"), EPCGDataType::Point);
	return PinProperties;
}

FPCGElementPtr UGetPointContext::CreateElement() const
{
	return MakeShared<FGetPointElement>();
}

bool FGetPointElement::ExecuteInternal(FPCGContext* Context) const
{
	if (!Context) return false;
	TArray<FPCGTaggedData> Inputs = Context->InputData.GetInputs();
	if (Inputs.IsEmpty() )
		return true;
	const UGetPointContext* Settings = Context->GetInputSettings<UGetPointContext>();
	// Create output handle
	FPCGTaggedData& Output = Context->OutputData.TaggedData.Add_GetRef(FPCGTaggedData());
	TArray<FPCGTaggedData> Input =	Context->InputData.GetInputsByPin(TEXT("In"));
	
	// Create new point data
	UPCGPointData* OutputData = NewObject<UPCGPointData>();
	Output.Data = OutputData;

	// iterator for the multiple data set pins that cn be connected
	for (const FPCGTaggedData& TaggedData : Input)
	{
		UPCGPointData* PointData = Cast<UPCGPointData>(TaggedData.Data);
		if(IsValid(PointData) && PointData->GetPoints().Num() > 0)
		{
			// get last for first, depending on setting
			switch ( Settings->Mode)
			{
				case Last:
						OutputData->GetMutablePoints().Add(PointData->GetPoints().Last());
					break;
				case First:
						OutputData->GetMutablePoints().Add(PointData->GetPoints()[0]);
					break;
				case StartAndEnd:
						OutputData->GetMutablePoints().Add(PointData->GetPoints().Last());
						OutputData->GetMutablePoints().Add(PointData->GetPoints()[0]);
					break;
			}
		}
	}


	return true;
}
