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
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	
	NadjiFizickiHandleKomponentu();
	NadjiInputKomponentu();
	
}

void UGrabber::NadjiFizickiHandleKomponentu()
{
	// pronacli FizickiHandler

	FizickiHandler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (FizickiHandler)
	{
		// nadjen
		UE_LOG(LogTemp, Warning, TEXT("Je nadjen Fizicki Handler %s"), *GetOwner()->GetName())
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Nije nadjen Fizicki Handler %s"), *GetOwner()->GetName())
	}
}

void UGrabber::NadjiInputKomponentu()
{
	// pronadji InputComponent

	InputKomponenta = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputKomponenta)
	{
		// nadjen
		UE_LOG(LogTemp, Warning, TEXT("Je nadjen input komponenta %s"), *GetOwner()->GetName())

		// povezi input za Zgrabi
		InputKomponenta->BindAction("Zgrabi", IE_Pressed, this, &UGrabber::Zgrabi);

		// povezi input za Otpusti
		InputKomponenta->BindAction("Zgrabi", IE_Released, this, &UGrabber::Otpusti);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Nije nadjen input komponenta %s"), *GetOwner()->GetName())
	}
}



void UGrabber::Zgrabi() 
{
	UE_LOG(LogTemp, Warning, TEXT("Zgrabi stisnut"))

	// Line trace i pokusaj doci u doseg aktora sa physic body collision chanel postavljenim
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();

	auto ActorHit = HitResult.GetActor();

	// ako dodjemo do neceg spojiti s fizickim handleom
	if (ActorHit) {
		// spojiti fizicki handle
		FizickiHandler->GrabComponent(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			true
		);
	}
}

void UGrabber::Otpusti()
{
	UE_LOG(LogTemp, Warning, TEXT("Zgrabi pusten"))

	// TODO release phyics handle
	FizickiHandler->ReleaseComponent();
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

	// ako je fizicki handle spojen
	if (FizickiHandler->GrabbedComponent)
		// micati objekt koji je spojen
		{
		FizickiHandler->SetTargetLocation(LineTraceEnd);
	}

	
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
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
	return LineTracePogodak;
}

