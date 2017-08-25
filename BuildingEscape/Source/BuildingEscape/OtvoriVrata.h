// Copyright Luka Gudic 2017

#pragma once

#include "Components/ActorComponent.h"
#include "OtvoriVrata.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOtvoriVrata : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOtvoriVrata();

	// Called when the game starts
	virtual void BeginPlay() override;

	void OtvoriVrata();
	void ZatvoriVrata();
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
	UPROPERTY(VisibleAnywhere)
	float KutOtvaranja = -90.0f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PaletaPritiska = nullptr;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 2.0f;

	float LastDoorOpenTime;
	AActor* Owner;

	// return total mass in kgs
	float GetTotalMassOfActorOnPlate();
};
