// Written by joshgreaves.

#pragma once

#include "HolodeckAgent.h"
#include "HolodeckPawnController.h"
#include "Components/SceneComponent.h"
#include "HolodeckSensor.generated.h"

/**
  * HolodeckSensor
  * Abstract base class for sensors within holodeck
  * Handles publishing sensor data
  * To override, you must implement:
  *		GetDataKey
  *		GetDataLength
  *		TickSensorComponent
  * And in BeginPlay you must call
  *		Super::BeginPlay
  *	But you cannot override:
  *		TickComponent
  */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), abstract )
class HOLODECK_API UHolodeckSensor : public USceneComponent
{
	GENERATED_BODY()

public:	
	/**
	  * Default Constructor
	  */
	UHolodeckSensor();

	/**
	  * Gets the controller and sets up
	  * Subclasses should make sure to call Super::BeginPlay()
	  */
	virtual void BeginPlay() override;
	
	/**
	  * Publishes sensor data each tick
	  * Subclasses should NOT override this function.
	  * Instead, they should override TickSensorComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
	  * TickSensorComponent is called from this
	  */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	/**
	  * Must be overridden by subclass
	  * Set the name for the data
	  * e.g. return "MyNewSensor"
	  */
	virtual FString GetDataKey() { check(0 && "You must override GetDataKey"); return ""; };

	/**
	  * Must be overridden by subclass
	  * Set the number of data items
	  * e.g. return 100
	  */
	virtual int GetNumItems() { check(0 && "You must override getNumItems"); return 0; };

	/**
	  * Must be overridden by subclass
	  * Set the size of each data item
	  * e.g. return sizeof(float)
	  */
	virtual int GetItemSize() { check(0 && "You must override getItemSize"); return 0; };

	/**
	  * Must be overridden by subclass
	  * Handles the logic for ticking the sensor
	  * Make sure to set the data,
	  * Cast Buffer into the right kind of pointer and set the data.
	  */
	virtual void TickSensorComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) { 
		check(0 && "You must override TickSensorComponent"); };

	// Allows you to turn the sensor on and off in the editor
	UPROPERTY(EditAnywhere)
	bool bOn;

	FString AgentName;
	FString SensorName;

	AHolodeckPawnController* Controller;
	void* Buffer;
};
