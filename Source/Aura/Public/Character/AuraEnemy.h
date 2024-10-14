// Copyright Al Learning

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AAuraEnemy();
	virtual void BeginPlay() override;
	virtual void HighlightActor() override;
	virtual void UnhighlightActor() override;

	/** Combat interface **/
	virtual int32 GetPlayerLevel() override;

	UPROPERTY(BlueprintReadWrite)
	bool isHighlighted;

protected:
	virtual void InitAbilityActorInfo() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Class Defaults")
	int32 Level = 1;
};
