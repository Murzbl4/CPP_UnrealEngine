

#pragma once
#include "CoreMinimal.h"
#include "Sound/SoundBase.h"
#include "EFireModeEnum.h"
#include "WeaponStruct_CPP.generated.h"

USTRUCT(BlueprintType)
struct FWeaponStruct
{
    GENERATED_BODY()

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Structure")
        int32 AmmoCapacity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Structure")
        int32 AmmoCurrent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Structure")
        int32 MagazineCapacity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Structure")
        int32 MagazineCurrent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Structure")
        int32 Multishot;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Structure")
        int32 Burst;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Structure")
        float BurstFireRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Structure")
        float FireRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Structure")
        float Damage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Structure")
        float HSMultiplier;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Structure")
        float Accuracy;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Structure")
        TArray<float> HorizontalRecoil;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Structure")
        TArray<float> VerticalRecoil;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Structure")
        float RecoilSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Structure")
        float ReloadSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Structure")
        float ReloadSpeed_full;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Structure")
        float ReloadSpeed_NoFull;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Structure")
        USoundBase* SoundBullet;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Structure")
        USoundBase* SoundBullet_Silencer;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Structure")
        USoundBase* SoundReload;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Structure")
        UParticleSystemComponent* Impact;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Structure")
        UParticleSystemComponent* Flash;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Structure")
        UParticleSystemComponent* Bullet_Speed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Structure")
        bool Projectile;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Structure")
        bool Scope;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Structure")
        bool Secondary;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Structure")
        bool Additional;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Structure")
        bool Reload1by1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Structure")
        EFireModeEnum FireMode;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Structure")
        EFireModeEnum FireMode_1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Structure")
        EFireModeEnum FireMode_2;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Structure")
        int32 Weapon_id_in_table;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Structure")
        bool Weapon_non_animation_standart;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Structure")
        TArray<float> Ballistic_speed_Bullet;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Structure")
        bool BoltAction;
};
