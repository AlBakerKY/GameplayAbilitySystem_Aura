// Copyright Al Learning

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataUnderMouse.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMouseTargetDataSignature, const FGameplayAbilityTargetDataHandle&, DataHandle);
/**
 * This class is designed to support passing the user mouse click data from a client to the server to assist with launching
 * a projectile towards an enemy.  If this were a game like doom, this probably would not be necessary, we we know where our
 * character is aimed.  In this case, however, we do not, so we need that mouse input.
 *
 * Note: For this to work properly, we will need to initialize sending this data under AuraAssetManager with
 * UAbilitySystemGlobals::Get().InitGlobalData();
 *
 * THIS IS NOT TRUE AFTER 5.3
 *
 *AU 118
 * 
 */
UCLASS()
class AURA_API UTargetDataUnderMouse : public UAbilityTask
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FMouseTargetDataSignature ValidData;

	UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (DisplayName = "TargetDataUnderMouse",HidePin= "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly="true"))
	static UTargetDataUnderMouse* CreateTargetUnderMouse(UGameplayAbility* OwningAbility);

private:

	virtual void Activate() override;
	void SendMouseCursorData();

	void OnTargetReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag);
};
