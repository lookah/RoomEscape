// Copyright Luka Gudic 2017

#include "BuildingEscape.h"
#include "OtvoriVrata.h"


// Sets default values for this component's properties
UOtvoriVrata::UOtvoriVrata()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOtvoriVrata::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Akcija otvaranja vrata"))

	// nadji vlasnika aktora
	AActor* Owner = GetOwner();

	//set the rotatior
	FRotator NovaRotacija = FRotator(0.0f, -78.0f, 0.0f);
	
	// set the door rotation
	Owner->SetActorRotation(NovaRotacija);
}


// Called every frame
void UOtvoriVrata::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

