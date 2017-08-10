// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor() {
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay() {
    Super::BeginPlay();

//    ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
    owner = GetOwner();
}

void UOpenDoor::OpenDoor() const {
    owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (GetTotalMassOfActorsOnPlate() > TriggerMass) {
        LastDoorOpenTime = GetWorld()->GetTimeSeconds();
        OpenDoor();
    }

    if (GetWorld()->GetTimeSeconds() > LastDoorOpenTime + DoorCloseDelay) {
        CloseDoor();
    }
}

void UOpenDoor::CloseDoor() const {
    owner->SetActorRotation(FRotator(0.f, 0.f, 0.f));
}

float UOpenDoor::GetTotalMassOfActorsOnPlate() {
    float TotalMass = 0.f;

    TArray<AActor *> OverlappingActors;
    PressurePlate->GetOverlappingActors(OUT OverlappingActors);

    for (const AActor *Actor : OverlappingActors) {
        TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
        UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate"), *Actor->GetName());
    }
    return TotalMass;
}

