

#pragma once

#include "CoreMinimal.h"
#include "FHitPlayerData.generated.h"


USTRUCT(BlueprintType)
struct FHitPlayerData
{
    GENERATED_BODY()

        UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float Damage;

        UPROPERTY(EditAnywhere, BlueprintReadWrite)
            FHitResult Hit ;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FVector HitDirection;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        bool Headshot;

    
};
