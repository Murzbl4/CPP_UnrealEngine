

#pragma once

#include "FHitPlayerData.h"
#include "WeaponStruct_CPP.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponMaster_CPP.generated.h"

UCLASS()
class SHOOTER_API AWeaponMaster_CPP : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponMaster_CPP();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Accuracy_Multiplier_Sprinting_While_Aiming_CPP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Accuracy_Multiplier_Idle_While_Aiming_CPP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Accuracy_Multiplier_Walking_While_Aiming_CPP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Accuracy_Multiplier_Sprinting_CPP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Accuracy_Multiplier_Idle_CPP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Accuracy_Multiplier_Walking_CPP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MinDistDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxDistDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<FString, int32> MaterialBulletResitSurfaceMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Character")
		FWeaponStruct WeaponStruct;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Character")
		TMap<AActor*, FHitPlayerData> HitPlayerData;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "MyFirstTest")
		void CalcBulletDrop_Gun(ABasePawn_CPP* BasePawn, float PadenieBullet, float BulletDistance, TArray<AActor*>& ActorsHit, TArray<FVector>& LocationHit, TArray<FRotator>& RotationHit, TArray<float>& Damage,FVector& StartShot, FVector& EndShot, FVector& EndShot_target, TMap<AActor*, FHitPlayerData>& HitDataPlayer,TArray<FVector>& LocationHits);

	const float CalcDamage(int32 Index, FVector Start, const FHitResult& Hit);
	const float MapRangeClamped(float Value, float InRangeA, float InRangeB, float OutRangeA, float OutRangeB);
};


