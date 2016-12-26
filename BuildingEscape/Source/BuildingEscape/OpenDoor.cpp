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
	if (ActorThatOpens == nullptr) {
		ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	}
	Owner = GetOwner();
	CloseAngle = Owner->GetTransform().GetRotation().Euler().Z;
}


void UOpenDoor::OpenDoor()
{
	Owner->SetActorRotation(FRotator(0.0f, CloseAngle + OpenAngleOffset, 0.0f));
	DoorOpened = true;
}

void UOpenDoor::CloseDoor()
{
	Owner->SetActorRotation(FRotator(0.0f, CloseAngle, 0.0f));
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// If ActorThatOpens is in the volume of PressurePlate then OpenDoor()
	if (PressurePlate != nullptr)
	{
		if (PressurePlate->IsOverlappingActor(ActorThatOpens))
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

}

