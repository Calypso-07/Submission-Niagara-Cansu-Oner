
#include "WaterHose.h"

#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "Engine/Engine.h"

AWaterHose::AWaterHose()
{
    PrimaryActorTick.bCanEverTick = false;

    WaterNiagara = CreateDefaultSubobject<UNiagaraComponent>(
        TEXT("WaterNiagara")
    );

    RootComponent = WaterNiagara;
    WaterNiagara->SetAutoActivate(false);
}

void AWaterHose::BeginPlay()
{
    Super::BeginPlay();

    WaterNiagara->SetVariableObject(
        FName(TEXT("User.ParticleCallback")),
        this
    );

    WaterNiagara->Activate(true);
}

void AWaterHose::ReceiveParticleData_Implementation(
    const TArray<FBasicParticleData>& Data,
    UNiagaraSystem* NiagaraSystem,
    const FVector& SimulationPositionOffset
)
{
    if (Data.IsEmpty())
    {
        return;
    }

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(
            1,
            0.2f,
            FColor::Cyan,
            FString::Printf(
                TEXT("Water collisions: %d"),
                Data.Num()
            )
        );
    }

    for (const FBasicParticleData& Particle : Data)
    {
        const FVector HitPosition =
            Particle.Position + SimulationPositionOffset;

        UE_LOG(
            LogTemp,
            Log,
            TEXT("Water particle collision: %s"),
            *HitPosition.ToString()
        );
    }
}
