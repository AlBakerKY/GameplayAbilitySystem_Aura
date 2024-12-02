// Copyright Al Learning


#include "AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"

#include "AbilitySystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AbilitySystemComponent.h"
#include "Player/AuraPlayerController.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse* Obj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	return Obj;
}

void UTargetDataUnderMouse::Activate()
{
	// Case where we don't need to to call super
	// Super::Activate();

	const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();
	if (bIsLocallyControlled)
	{
		SendMouseCursorData();
	}
	else
	{
		const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
		const FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(SpecHandle, ActivationPredictionKey).AddUObject(
			this, &UTargetDataUnderMouse::OnTargetReplicatedCallback);
		// bCalled delegate is telling the server whether or not play data has arrived
		const bool bCalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, ActivationPredictionKey);
		if (!bCalledDelegate)
		{
			SetWaitingOnRemotePlayerData();
		}
	}
}

void UTargetDataUnderMouse::SendMouseCursorData()
{
	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());
	FHitResult HitResult;
	APlayerController* AuraPlayerController = Cast<AAuraPlayerController>(GetWorld()->GetFirstPlayerController());
	if (AuraPlayerController)
	{
		AuraPlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	}
	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	Data->HitResult = HitResult;
	FGameplayAbilityTargetDataHandle DataHandle;
	DataHandle.Add(Data);
	AbilitySystemComponent->ServerSetReplicatedTargetData(
		GetAbilitySpecHandle(), GetActivationPredictionKey(),
		DataHandle,
		FGameplayTag(),
		AbilitySystemComponent->ScopedPredictionKey);

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}

// This will be called only when receiving target data from the clients
void UTargetDataUnderMouse::OnTargetReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle,
                                                       FGameplayTag ActivationTag)
{
		AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}
