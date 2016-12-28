// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();	

	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
	float TimeTilDoorCloseTriggered = 1.0f;
	bool DoorOpened = false;

	UPROPERTY(EditAnywhere)
		int32 CloseAngle = 0; // angle of closed door

	UPROPERTY(EditAnywhere)
		int32 OpenAngleOffset = 90; // degrees to open door to from Closed door angle. ie. 90, -90, 45, -45, etc

	UPROPERTY(EditAnywhere)
		int32 TimeTilDoorClosed = 1.0f; // seconds until door closes

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate; // trigger volume to open door

	float UOpenDoor::GetMassOfActors();
};
