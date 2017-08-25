// Copyright Luka Gudic 2017

#include "BuildingEscape.h"
#include "Grabber.h"

#define OUT


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();


	UE_LOG(LogTemp, Warning, TEXT("Grabber pocinje raditi"));
	// ...
	
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	/// natjerati PlayerViewpoint -- gdje su i gdje gledaju
		
	FVector PogledIgracaLokacija;
	FRotator PogledIgracaRotacija;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PogledIgracaLokacija, 
		OUT PogledIgracaRotacija
	);

	/// logiraj rotaciju i lokaciju 

	/*UE_LOG(LogTemp, Warning, TEXT("Lokacija igraca: %s Rotacija igraca: %s"),
			*PogledIgracaLokacija.ToString(),
			*PogledIgracaRotacija.ToString()
	)*/

	/// prikazati dohvat igraca s crvenom linijom 

	FVector LineTraceEnd = PogledIgracaLokacija + PogledIgracaRotacija.Vector() * Reach;

	DrawDebugLine(
		GetWorld(),
		PogledIgracaLokacija,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		10.f
	);

	/// Setup query parametre
	FCollisionQueryParams TraceParametri(FName(TEXT("")), false, GetOwner());

	/// Line-trace (Ray-cast) to reach distance
	FHitResult LineTracePogodak;
	GetWorld()->LineTraceSingleByObjectType(
		OUT LineTracePogodak,
		PogledIgracaLokacija,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParametri
	);

	/// See what we hit

	AActor* AktorPogodjen = LineTracePogodak.GetActor();
	if (AktorPogodjen) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Pogodjen aktor: %s"), *AktorPogodjen->GetName())
	}
	// ...
}

