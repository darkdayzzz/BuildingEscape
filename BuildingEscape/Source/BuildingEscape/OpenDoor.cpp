// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// find the owning actor
	AActor* Owner = GetOwner();
	int32 OldRotationDeg = Owner->GetTransform().GetRotation().Euler().Z;
	// set the door rotation
	FRotator NewRotation = FRotator(0.0f, 180.0f, 0.0f);
	Owner->SetActorRotation(NewRotation);
	int32 NewRotationDeg = Owner->GetTransform().GetRotation().Euler().Z;
	UE_LOG(LogTemp, Warning, TEXT("Door was at %i degrees and now at %i degrees"), OldRotationDeg, NewRotationDeg);
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

