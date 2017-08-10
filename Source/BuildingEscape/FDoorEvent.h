// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "FDoorEvent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenRequest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseRequest);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))

class BUILDINGESCAPE_API UOpenDoor : public UActorComponent {
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UOpenDoor();

    // Called every frame
    virtual void
    TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

    UPROPERTY(BlueprintAssignable)
    FOnOpenRequest OnOpen;

    UPROPERTY(BlueprintAssignable)
    FOnCloseRequest OnClose;

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere)
    float TriggerMass = 50.f;

    UPROPERTY(EditAnywhere)
    ATriggerVolume *PressurePlate = nullptr;

    AActor *Owner = nullptr;

    float GetTotalMassOfActorsOnPlate();
};
