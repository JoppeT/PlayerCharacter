// Player Controller by Jacob Tjernström


#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT(text), fstring))
#include "MyCharacter2.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AMyCharacter2::AMyCharacter2()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

bool AMyCharacter2::CanBeSeenFrom(const FVector& ObserverLocation, FVector& OutSeenLocation, int32& NumberOfLoSChecksPerformed, float& OutSightStrength, const AActor* IgnoreActor) const
{
	static const FName NAME_AILineOfSight = FName(TEXT("TestPawnLineOfSight"));
 
	FHitResult HitResult;

	// First check if the whole actor is visible, if so return the actor location

	const bool bHit = GetWorld()->LineTraceSingleByObjectType(HitResult, ObserverLocation, GetActorLocation()
		, FCollisionObjectQueryParams(/*ECC_TO_BITFIELD(ECC_Pawn) | */ECC_TO_BITFIELD(ECC_WorldDynamic) | ECC_TO_BITFIELD(ECC_WorldStatic))
		, FCollisionQueryParams(NAME_AILineOfSight, true, IgnoreActor));

	NumberOfLoSChecksPerformed++;

	if (bHit == false || (HitResult.Actor.IsValid() && HitResult.Actor->IsOwnedBy(this)))
	{
		//DrawDebugLine(GetWorld(), ObserverLocation, GetActorLocation(), FColor::Red, false, 0.1f);
		OutSeenLocation = GetActorLocation();
		OutSightStrength = 1;

		return true;
	}

	// Otherwise loop through the specified bones until a visible one is found

	TArray<FName> strongSockets = { "spine_01", "spine_02"/*, "spine_03"*/ };
 
	for (int i = 0; i < strongSockets.Num(); i++)
	{
		FVector socketLocation = GetMesh()->GetSocketLocation(strongSockets[i]);
 
		const bool bHitSocket = GetWorld()->LineTraceSingleByObjectType(HitResult, ObserverLocation, socketLocation
			, FCollisionObjectQueryParams(/*ECC_TO_BITFIELD(ECC_Pawn) | */ECC_TO_BITFIELD(ECC_WorldDynamic) | ECC_TO_BITFIELD(ECC_WorldStatic))
			, FCollisionQueryParams(NAME_AILineOfSight, true, IgnoreActor));
 
		NumberOfLoSChecksPerformed++;
 
		if (bHitSocket == false || (HitResult.Actor.IsValid() && HitResult.Actor->IsOwnedBy(this))) {
			OutSeenLocation = socketLocation;
			OutSightStrength = 1;
			//GEngine->AddOnScreenDebugMessage(-1, 0.05f, FColor::Red, FString(GetMesh()->GetSocketBoneName(strongSockets[i]).ToString()));
			//DrawDebugLine(GetWorld(), ObserverLocation, socketLocation, FColor::Green, false, 0.1f);
 
			return true;
		}
	}

	TArray<FName> weakSockets = { "lowerarm_l", "lowerarm_r", "neck_01" };


	for (int i = 0; i < weakSockets.Num(); i++)
	{
		FVector socketLocation = GetMesh()->GetSocketLocation(weakSockets[i]);

		const bool bHitSocket = GetWorld()->LineTraceSingleByObjectType(HitResult, ObserverLocation, socketLocation
			, FCollisionObjectQueryParams(ECC_TO_BITFIELD(ECC_Pawn) | ECC_TO_BITFIELD(ECC_WorldDynamic) | ECC_TO_BITFIELD(ECC_WorldStatic))
			, FCollisionQueryParams(NAME_AILineOfSight, true, IgnoreActor));

		NumberOfLoSChecksPerformed++;

		if (bHitSocket == false || (HitResult.Actor.IsValid() && HitResult.Actor->IsOwnedBy(this))) {
			OutSeenLocation = socketLocation;
			OutSightStrength = 0.25;
			//GEngine->AddOnScreenDebugMessage(-1, 0.05f, FColor::Red, FString(GetMesh()->GetSocketBoneName(weakSockets[i]).ToString()));
			//DrawDebugLine(GetWorld(), ObserverLocation, socketLocation, FColor::Green, false, 0.1f);

			return true;
		}
	}
 
	OutSightStrength = 0;
	return false;
}


// Called when the game starts or when spawned
void AMyCharacter2::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter2::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

