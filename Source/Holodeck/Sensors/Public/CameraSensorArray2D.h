// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Holodeck.h"

#include "HolodeckPawnController.h"
#include "HolodeckSensor.h"
#include "HolodeckViewportClient.h"

#include "CameraSensorArray2D.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class HOLODECK_API UCameraSensorArray2D : public UHolodeckSensor {
	GENERATED_BODY()

public:	
	/**
	  * Default Constructor.
	  */
	UCameraSensorArray2D();

	/**
	  * BeginPlay
	  * Called at the start of the game.
	  */
	void BeginPlay() override;

	void Capture(TMap<FString, FString>& output);

protected:
	virtual FString GetDataKey() override;
	virtual int GetNumItems() override;
	virtual int GetItemSize() override;
	void TickSensorComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) override;

private:

	char* ResultArray;

	// The number of channels in an RGB image
	const static int NUM_RGB_CHANNELS = 3;
	// The number of channels in a grayscale image
	const static int NUM_GRAYSCALE_CHANNELS = 1;
	// The number of chars required to display numbers 0-255 in hexadecimal
	const static int HEX_COLOR_WIDTH = 2;

	TArray<USceneCaptureComponent2D*> AAttachedSceneCaptureComponents2D;

	const static char RGBConv[256][2];
};

