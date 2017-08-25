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
	FizickiHandler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (FizickiHandler == nullptr)
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
		InputKomponenta->BindAction("Zgrabi", IE_Pressed, this, &UGrabber::Zgrabi);
		InputKomponenta->BindAction("Zgrabi", IE_Released, this, &UGrabber::Otpusti);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Nije nadjen input komponenta %s"), *GetOwner()->GetName())
	}
}



void UGrabber::Zgrabi() {

	// Line trace i pokusaj doci u doseg aktora sa physic body collision chanel postavljenim
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

	if (!FizickiHandler) { return; }
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
	if (!FizickiHandler) { return; }
	FizickiHandler->ReleaseComponent();
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ako je fizicki handle spojen
	if (!FizickiHandler) { return; }
	if (FizickiHandler->GrabbedComponent)
		// micati objekt koji je spojen
		{
		FizickiHandler->SetTargetLocation(GetReachLineEnd());
	}

	
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	FCollisionQueryParams TraceParametri(FName(TEXT("")), false, GetOwner());
	FHitResult LineTracePogodak;
	GetWorld()->LineTraceSingleByObjectType(
		OUT LineTracePogodak,
		GetReachLineStart(),
		GetReachLineEnd(),
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

FVector UGrabber::GetReachLineEnd() 
{
	/// natjerati PlayerViewpoint -- gdje su i gdje gledaju
	FVector PogledIgracaLokacija;
	FRotator PogledIgracaRotacija;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PogledIgracaLokacija,
		OUT PogledIgracaRotacija
	);
	return PogledIgracaLokacija + PogledIgracaRotacija.Vector() * Reach;
}

FVector UGrabber::GetReachLineStart()
{
	FVector PogledIgracaLokacija;
	FRotator PogledIgracaRotacija;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PogledIgracaLokacija,
		OUT PogledIgracaRotacija
	);
	return PogledIgracaLokacija;
}

