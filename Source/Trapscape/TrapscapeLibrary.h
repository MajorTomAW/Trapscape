#pragma once

#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "BaseClasses/Buildings/BPBuildingBase.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TrapscapeLibrary.generated.h"
UENUM(BlueprintType)
enum class EBuildingType : uint8
 {
 	Wall,
	 Defense,
	 Trap
 };

USTRUCT(BlueprintType)
struct FBuildingInfo : public FTableRowBase
{
	GENERATED_BODY();
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText Tag = FText::FromString("");
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* Icon = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EBuildingType Type = EBuildingType::Wall;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Cost = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<ABPBuildingBase> Class;
};
/**
 * 
 */
UCLASS()
class TRAPSCAPE_API UTrapscapeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};
