// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber() {
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay() {
    Super::BeginPlay();

    FindPhysicsHandleComponent();
    SetupInputComponent();

}

void UGrabber::SetupInputComponent() {
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

    if (InputComponent) {
        UE_LOG(LogTemp, Warning, TEXT("%s has Grabber and has InputComponent!"), *GetOwner()->GetName());
        InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
        InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
    } else {
        UE_LOG(LogTemp, Error, TEXT("%s has Grabber but lacks InputComponent!"), *GetOwner()->GetName());
    }
}

void UGrabber::FindPhysicsHandleComponent() {
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

    if (!PhysicsHandle) {
        UE_LOG(LogTemp, Error, TEXT("%s has Grabber but lacks PhysicsHandle!"), *GetOwner()->GetName());
    }
}

void UGrabber::Grab() {
    auto HitResult = GetFirstPhysicsBodyInReach();
    auto ComponentToGrab = HitResult.GetComponent();
    auto ActorHit = HitResult.GetActor();

    // If we hit something then attach a physics handle
    if (ActorHit) {
        PhysicsHandle->GrabComponentAtLocationWithRotation(
                ComponentToGrab,
                NAME_None,
                ComponentToGrab->GetOwner()->GetActorLocation(),
                ComponentToGrab->GetOwner()->GetActorRotation());
    }
}

void UGrabber::Release() {
    // Release the physics handle
    PhysicsHandle->ReleaseComponent();
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() {
    const FCollisionQueryParams &collisionQueryParams =
            FCollisionQueryParams(FName(TEXT("")), false, GetOwner());

    FHitResult HitResult;
    GetWorld()->LineTraceSingleByObjectType(
            OUT HitResult,
            PlayerViewPointLocation,
            LineTraceEnd,
            FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
            collisionQueryParams
    );
    return HitResult;
}

void UGrabber::UpdatePickingLocation() {
    FRotator PlayerViewPointRotation;
    PlayerViewPointLocation;
    GetOwner()->GetInstigatorController()->GetPlayerViewPoint(
            OUT PlayerViewPointLocation,
            OUT PlayerViewPointRotation
    );

    LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * REACH;
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    UpdatePickingLocation();
    if (PhysicsHandle->GrabbedComponent) {
        PhysicsHandle->SetTargetLocation(LineTraceEnd);
    }
}

