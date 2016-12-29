// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();	

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UPROPERTY(BluePrintAssignable)
		FDoorEvent OnOpen;

	UPROPERTY(BluePrintAssignable)
		FDoorEvent OnClose;

	UPROPERTY(EditAnywhere)
		float OpenDegrees = 90.f;

	UPROPERTY(EditAnywhere)
		float TriggerMass = 50.0f;

private:
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr; // trigger volume to open door

	float UOpenDoor::GetMassOfActors();
};
