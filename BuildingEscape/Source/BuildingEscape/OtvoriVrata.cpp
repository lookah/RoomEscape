// Copyright Luka Gudic 2017

#include "BuildingEscape.h"
#include "OtvoriVrata.h"

#define OUT


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
	Owner = GetOwner();
		
}

void UOtvoriVrata::OtvoriVrata()
{
	// set the door rotation
	Owner->SetActorRotation(FRotator(0.0f, KutOtvaranja, 0.0f));
}

void UOtvoriVrata::ZatvoriVrata()
{

	// set the door rotation
	Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}


// Called every frame
void UOtvoriVrata::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (GetTotalMassOfActorOnPlate() > 25.0f) // TODO Make into a parameter 
	{	
		UE_LOG(LogTemp, Warning, TEXT("Otvaram vrata"))
		OtvoriVrata();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
	{
		ZatvoriVrata();
	}

	GetWorld()->GetTimeSeconds();
}

float UOtvoriVrata::GetTotalMassOfActorOnPlate()
{
	float UkupnaMasa = 0.0f;

	// nadji sve aktore na plateu
	TArray<AActor*> OverlappingActors;
	if (!PaletaPritiska) { return UkupnaMasa; }
	PaletaPritiska->GetOverlappingActors(OUT OverlappingActors);

	// iteriraj po svima i zbroji im masu
	for (const auto* Aktor : OverlappingActors) {
		UE_LOG(LogTemp, Warning, TEXT("Aktor na plaeti je %s"), *Aktor->GetName())
		UkupnaMasa += Aktor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	UE_LOG(LogTemp, Warning, TEXT("Masa je %f"), UkupnaMasa)
	return UkupnaMasa;
}