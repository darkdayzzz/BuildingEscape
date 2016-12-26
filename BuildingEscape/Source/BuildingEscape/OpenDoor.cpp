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
	AActor* Owner = GetOwner();
	FRotator StartRotation = FRotator(0.0f, CloseAngle, 0.0f);
	CloseAngle = Owner->GetTransform().GetRotation().Euler().Z;
}


void UOpenDoor::OpenDoor(bool bOpen)
{
	// find the owning actor
	AActor* Owner = GetOwner();
	int32 OldRotationDeg = Owner->GetTransform().GetRotation().Euler().Z;
	if (((OldRotationDeg == CloseAngle) && bOpen) || ((OldRotationDeg != CloseAngle) && !bOpen)) {
		// change the door rotation
		FString ObjectName = GetOwner()->GetName();
		FRotator NewRotation = FRotator(0.0f, bOpen ? CloseAngle + OpenAngleOffset : CloseAngle, 0.0f);
		Owner->SetActorRotation(NewRotation);
		int32 NewRotationDeg = Owner->GetTransform().GetRotation().Euler().Z;
		UE_LOG(LogTemp, Warning, TEXT("Door was at %i degrees and now at %i degrees"), OldRotationDeg, NewRotationDeg);
	}
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
			OpenDoor(true);
		}
		else
		{
			OpenDoor(false);
		}
	}

}

