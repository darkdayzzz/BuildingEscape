// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "OpenDoor.h"

#define OUT

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
	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("No Pressure Plate value found. Check object %s has Pressure Plate set."), *(GetOwner()->GetName()));
	};
	CloseAngle = GetOwner()->GetTransform().GetRotation().Euler().Z;
}


void UOpenDoor::OpenDoor()
{
	OnOpenRequest.Broadcast();
	//GetOwner()->SetActorRotation(FRotator(0.0f, CloseAngle + OpenAngleOffset, 0.0f));
	DoorOpened = true;
}

void UOpenDoor::CloseDoor()
{
	GetOwner()->SetActorRotation(FRotator(0.0f, CloseAngle, 0.0f));
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// If total mass of actors on trigger is over x kg then OpenDoor()
	if (!PressurePlate) { return; }
	if (GetMassOfActors()>50.0f)
	{
		OpenDoor();
	}
	else
	{
		if (DoorOpened) {
			TimeTilDoorCloseTriggered = GetWorld()->GetTimeSeconds();
			DoorOpened = false;
		};
		if (GetWorld()->GetTimeSeconds() - TimeTilDoorCloseTriggered > TimeTilDoorClosed) {
			CloseDoor();
		};
	};
}

float UOpenDoor::GetMassOfActors()
{
	if (!PressurePlate) { return 0.f; }
	float TotalMass = 0.f;
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	// iterate through overlapping actors and add mass
	for (const auto& Actor : OverlappingActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found this overlapping actor: %s"), *(Actor->GetName()));
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return TotalMass;
}