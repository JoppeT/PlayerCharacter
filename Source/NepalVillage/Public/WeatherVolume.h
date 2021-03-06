// Player Controller by Jacob Tjernström

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeatherVolume.generated.h"

UCLASS()
class NEPALVILLAGE_API AWeatherVolume : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AWeatherVolume();


	// Properties

	UPROPERTY(EditAnywhere, Category = "Properties", BlueprintReadWrite)
		bool ChangeStrength;
	UPROPERTY(EditAnywhere, Category = "Properties", BlueprintReadWrite, meta = (EditCondition = "ChangeStrength"))
		float NewStrength;

	UPROPERTY(EditAnywhere, Category = "Properties", BlueprintReadWrite)
		bool ChangeSpeed;
	UPROPERTY(EditAnywhere, Category = "Properties", BlueprintReadWrite, meta = (EditCondition = "ChangeSpeed"))
		float NewSpeed;

	UPROPERTY(EditAnywhere, Category = "Properties", BlueprintReadWrite)
		bool ChangeMinGustAmount;
	UPROPERTY(EditAnywhere, Category = "Properties", BlueprintReadWrite, meta = (EditCondition = "ChangeMinGustAmount"))
		float NewMinGustAmount;

	UPROPERTY(EditAnywhere, Category = "Properties", BlueprintReadWrite)
		bool ChangeMaxGustAmount;
	UPROPERTY(EditAnywhere, Category = "Properties", BlueprintReadWrite, meta = (EditCondition = "ChangeMaxGustAmount"))
		float NewMaxGustAmount;

	UPROPERTY(EditAnywhere, Category = "Properties", BlueprintReadWrite)
		bool ChangeRotation;
	UPROPERTY(EditAnywhere, Category = "Properties", BlueprintReadWrite, meta = (EditCondition = "ChangeRotation"))
		FRotator NewRotation;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
