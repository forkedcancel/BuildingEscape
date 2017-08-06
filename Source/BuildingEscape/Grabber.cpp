// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber() {
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}


// Called when the game starts
void UGrabber::BeginPlay() {
    Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));
}

void UGrabber::LogPlayerViewPoint() const {
    FRotator PlayerViewPointRotation;
    FVector PlayerViewPointLocation;
    GetOwner()->GetInstigatorController()->GetPlayerViewPoint(
            OUT PlayerViewPointLocation,
            OUT PlayerViewPointRotation
    );

//    UE_LOG(LogTemp, Warning, TEXT("%s %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());
    FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * REACH;//PlayerViewPointLocation + FVector(0.f, 0.f, REACH);

    DrawDebugLine(
      GetWorld(),
      PlayerViewPointLocation,
      LineTraceEnd,
      FColor(255, 0, 0),
      false,
      0.f,
      0,
      10.f
    );
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
    LogPlayerViewPoint();

}

