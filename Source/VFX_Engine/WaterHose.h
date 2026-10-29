
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraDataInterfaceExport.h"
#include "WaterHose.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;

UCLASS()
class VFX_ENGINE_API AWaterHose : public AActor,
    public INiagaraParticleCallbackHandler
{
    GENERATED_BODY()

public:
    AWaterHose();

    virtual void ReceiveParticleData_Implementation(
        const TArray<FBasicParticleData>& Data,
        UNiagaraSystem* NiagaraSystem,
        const FVector& SimulationPositionOffset
    ) override;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<UNiagaraComponent> WaterNiagara;
};
