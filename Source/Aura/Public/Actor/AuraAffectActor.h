// Copyright Al Learning

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraAffectActor.generated.h"


class UGameplayEffect;

UCLASS()
class AURA_API AAuraAffectActor : public AActor
{
	GENERATED_BODY()

public:
	AAuraAffectActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effects")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);
	

};
