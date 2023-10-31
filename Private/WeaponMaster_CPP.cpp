
#include "WeaponMaster_CPP.h"
#include "BasePawn_CPP.h"
#include "Camera/CameraComponent.h"
#include <random>
#include "DrawDebugHelpers.h"
#include "Components/PrimitiveComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include <chrono>
#include <thread>
#include "Engine.h"


// Sets default values
AWeaponMaster_CPP::AWeaponMaster_CPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWeaponMaster_CPP::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponMaster_CPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponMaster_CPP::CalcBulletDrop_Gun(ABasePawn_CPP* BasePawn, float PadenieBullet, float BulletDistance, TArray<AActor*>& ActorsHit, TArray<FVector>& LocationHit, TArray<FRotator>& RotationHit, TArray<float>& Damage, FVector& StartShot, FVector& EndShot, FVector& EndShot_target, TMap<AActor*, FHitPlayerData>& HitDataPlayer, TArray<FVector>& LocationHits)
{
    //GET TRACE START START FUNCTION!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // 
    // 
    FHitPlayerData HitPlayer_str;

    float AccuracyMultiplier;
    float AccuracyMultiplier_1;
    float AccuracyMultiplier_2;
    //GetBaseAimRotation
    FRotator AimRotation = BasePawn->GetControlRotation();

    //GetForwardVector
    FRotationMatrix ModifiedRotationMatrix_1(AimRotation);
    FVector ForwardVectorAimRotation = ModifiedRotationMatrix_1.GetUnitAxis(EAxis::X);

    //GetWorldLocation
    UCameraComponent* Camera = BasePawn->FindComponentByClass<UCameraComponent>();
    FVector CameraLocation = Camera->GetComponentLocation();

    StartShot = CameraLocation;

    ForwardVectorAimRotation = ForwardVectorAimRotation * BulletDistance;
    FVector InVec = CameraLocation + ForwardVectorAimRotation;
    //GET TRACE START END FUNCTION!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // 
    // 
    //Get Accuracy Multiplier START FUNCTION!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // 
    // 
    FVector GetVelocity = BasePawn->GetVelocity();
    float VectorLength_GetAccuracy = GetVelocity.Size();
    if (VectorLength_GetAccuracy >= 10)
    {
        AccuracyMultiplier_1 = Accuracy_Multiplier_Walking_While_Aiming_CPP;
        AccuracyMultiplier_2 = Accuracy_Multiplier_Walking_CPP;
    }
    else
    {
        AccuracyMultiplier_1 = Accuracy_Multiplier_Idle_While_Aiming_CPP;
        AccuracyMultiplier_2 = Accuracy_Multiplier_Idle_CPP;
    }

    if (VectorLength_GetAccuracy > BasePawn->Normal_Walk_Speed_CPP)
    {
        AccuracyMultiplier_1 = Accuracy_Multiplier_Sprinting_While_Aiming_CPP;
        AccuracyMultiplier_2 = Accuracy_Multiplier_Sprinting_CPP;
    }

    if (BasePawn->IsAiming_CPP)
    {
        AccuracyMultiplier = AccuracyMultiplier_1;
    }
    else
    {
        AccuracyMultiplier = AccuracyMultiplier_2;
    }
    //Get Accuracy Multiplier END FUNCTION!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // 
    // 
    //Bullet Spread START FUNCTION!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // 
    // 
    float randomFloat_1 = FMath::FRandRange(WeaponStruct.Accuracy * AccuracyMultiplier * (-1), WeaponStruct.Accuracy * AccuracyMultiplier);
    float randomFloat_2 = FMath::FRandRange(WeaponStruct.Accuracy * AccuracyMultiplier * (-1), WeaponStruct.Accuracy * AccuracyMultiplier);
    float randomFloat_3 = FMath::FRandRange(WeaponStruct.Accuracy * AccuracyMultiplier * (-1), WeaponStruct.Accuracy * AccuracyMultiplier);
    FVector Target;
    EndShot_target = Target;
    Target.X = InVec.X + randomFloat_1;
    Target.Y = InVec.Y + randomFloat_2;
    Target.Z = InVec.Z + randomFloat_3;
    //Bullet Spread END FUNCTION!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // 
    //
    //CalcBulletDrop_Gun_START FUNCTION!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // 
    // 
    // FIND Look AT Rotation
    FVector Direction = Target - CameraLocation;
    FRotator FindLookAtRotation = FRotationMatrix::MakeFromX(Direction).Rotator();

    // Vector Length
    FVector BulletDrop = CameraLocation - Target;
    float VectorLength = BulletDrop.Size();

    VectorLength /= PadenieBullet;

    // Truncate
    VectorLength = (int32)VectorLength;

    // ForLoop
    int32 Index = 0;
    TArray<FHitResult> OutHits;
    FVector OutStartVector;
    while (Index <= VectorLength)
    {

        FRotator ModifiedRotation = FRotator(FindLookAtRotation.Pitch + (Index * (-0.25)), FindLookAtRotation.Yaw, FindLookAtRotation.Roll);

        //GetForwardVector
        FRotationMatrix ModifiedRotationMatrix(ModifiedRotation);
        FVector ModifiedForwardVector = ModifiedRotationMatrix.GetUnitAxis(EAxis::X);


        //Sum Vector
        OutStartVector = CameraLocation + ((Index * PadenieBullet) * ModifiedForwardVector);
        OutStartVector.Z = OutStartVector.Z + (Index * (-1));
        FVector OutEndVector = CameraLocation + (((Index + 1) * PadenieBullet) * ModifiedForwardVector);
        OutEndVector.Z = OutEndVector.Z + (Index * (-1));

        TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
        ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel3));
        ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));

        //Trace
        FCollisionQueryParams TraceParams(FName(TEXT("BulletTrace")), true, this);
        TraceParams.bTraceComplex = true;
        TraceParams.bReturnPhysicalMaterial = false;

        TArray<FHitResult> HitResults;
        GetWorld()->LineTraceMultiByObjectType(HitResults, OutStartVector, OutEndVector, FCollisionObjectQueryParams(ObjectTypes), TraceParams);

        //DrawDebugLine(GetWorld(), OutStartVector, OutEndVector, FColor::Purple, false, 360.0f, 0, 1.0f);
        for (const FHitResult& HitResult : HitResults)
        {
            OutHits.Add(HitResult);
        }
        Index++;
    }
    //CalcBulletDrop_Gun_END FUNCTION!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //
    //
    int32 IndexPenitration = 0;
    FString PhysMatNameString;

    for (const FHitResult& Hit : OutHits)
    {
        AActor* HitActor = Hit.GetActor();
        FVector ImpactPoint = Hit.ImpactPoint;
        LocationHits.Add(ImpactPoint);
        EndShot = ImpactPoint;
        float FinalDamage;
        FVector ImpactNormal = Hit.ImpactNormal;
        ImpactNormal = ImpactNormal * (-1);
        FVector XVector = FVector::CrossProduct(FVector::UpVector, ImpactNormal).GetSafeNormal();
        FVector ZVector = FVector::CrossProduct(ImpactNormal, XVector).GetSafeNormal();
        FMatrix RotationMatrix = FRotationMatrix::MakeFromXZ(XVector, ZVector);
        FRotator RotationFromXVector = RotationMatrix.Rotator();
        UPhysicalMaterial* HitPhysicalMaterial = Hit.PhysMaterial.Get(0);

        // ОПРЕДЕЛЕНИЕ ЧТО ЗА ФИЗИЧЕСКИЙ МАТЕРИАЛ
        UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(HitActor->GetRootComponent());

        //GEngine->AddOnScreenDebugMessage(-1, 300.0f, FColor::Red, PhysMatNameString);

        if (PrimitiveComponent != nullptr)
        {
            UMaterialInterface* MatInterface = PrimitiveComponent->GetMaterial(0);
            UPhysicalMaterial* PhysMat = nullptr;
            if (MatInterface != nullptr)
            {
                PhysMat = MatInterface->GetPhysicalMaterial(); // ОПРЕДЕЛЕНИЕ ЧТО ЗА ФИЗИЧЕСКИЙ МАТЕРИАЛ                                        
                FName PhysMatName = PhysMat->GetFName();
                PhysMatNameString = PhysMatName.ToString();

                int32 BulletResitSurfaceValue = 0;
                if (MaterialBulletResitSurfaceMap.Contains(PhysMatNameString))
                {
                    BulletResitSurfaceValue = *MaterialBulletResitSurfaceMap.Find(PhysMatNameString);
                    if (IndexPenitration < BulletResitSurfaceValue) {
                        FinalDamage = CalcDamage(IndexPenitration, CameraLocation, Hit);
                        ActorsHit.Add(Hit.GetActor());
                        LocationHit.Add(Hit.ImpactPoint);
                        RotationHit.Add(RotationFromXVector);
                        Damage.Add(FinalDamage);

                        HitPlayer_str.Damage = FinalDamage;
                        HitPlayer_str.Hit = Hit;
                        HitPlayer_str.HitDirection = CameraLocation;
                        HitPlayer_str.Headshot = false;            
                        AActor* Key = Hit.GetActor();
                        HitDataPlayer.Add(Key,HitPlayer_str);
                    }
                    else {
                        break;
                    }
                }
            }
        }
        IndexPenitration++;
    }

}

const float AWeaponMaster_CPP::CalcDamage(int32 Index, FVector Start, const FHitResult& Hit)
{
    AActor* HitActor = Hit.GetActor();
    FVector ImpactPoint_func = Hit.ImpactPoint;
    float multiplyDamagePenitration;
    float Damage = WeaponStruct.Damage;
    if (Index == 0) {
        multiplyDamagePenitration = 1;
    }
    else {
        multiplyDamagePenitration = Index;
    }
    Damage = Damage / multiplyDamagePenitration;
    FVector VectorLengthFunc_1 = ImpactPoint_func - Start;
    float VectorLength = VectorLengthFunc_1.Size();
    float result_MapRangeClamped = MapRangeClamped(VectorLength, MinDistDamage, MaxDistDamage, 1, 2);

    FString MessageVector = FString::Printf(TEXT("[%f, %f, %f]"), VectorLengthFunc_1.X, VectorLengthFunc_1.Y, VectorLengthFunc_1.Z);
    FString Messagefloat = FString::SanitizeFloat(result_MapRangeClamped);
    FString Messageint32 = FString::FromInt(multiplyDamagePenitration);
    if (VectorLength < MaxDistDamage) {
        Damage = Damage / result_MapRangeClamped;
    }
    else {
        Damage = 1;
    }
    if (VectorLength < MinDistDamage) {
        Damage = WeaponStruct.Damage / multiplyDamagePenitration;
    }

    Damage = Damage + WeaponStruct.Damage;

    return Damage;
}

const float AWeaponMaster_CPP::MapRangeClamped(float Value, float InRangeA, float InRangeB, float OutRangeA, float OutRangeB)
{
    // Код для учёта обратных значений, если InRangeA > InRangeB
    if (InRangeA > InRangeB)
    {
        float Temp = InRangeA;
        InRangeA = InRangeB;
        InRangeB = Temp;
    }

    // Ограничение входного значения в пределах InRangeA и InRangeB
    float ClampedValue = FMath::Clamp(Value, InRangeA, InRangeB);

    // Отображение значения на новый диапазон
    float MappedValue = ((ClampedValue - InRangeA) / (InRangeB - InRangeA)) * (OutRangeB - OutRangeA) + OutRangeA;

    // Ограничение выходного значения в пределах OutRangeA и OutRangeB
    float ClampedMappedValue = FMath::Clamp(MappedValue, OutRangeA, OutRangeB);

    return ClampedMappedValue;
}








