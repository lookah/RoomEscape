// Copyright Luka Gudic 2017

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
	
private:
	// reach koliko mozemo dosegnuti ispred igraca	
	float Reach = 100.f;

	UPhysicsHandleComponent* FizickiHandler = nullptr;
	void Zgrabi();

	UInputComponent* InputKomponenta = nullptr;
	void Otpusti();

	// nadji povezani fizicki handler komponentu
	void NadjiFizickiHandleKomponentu();

	// nadji input komponentu
	void NadjiInputKomponentu();

	// Return hit for first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();
};
