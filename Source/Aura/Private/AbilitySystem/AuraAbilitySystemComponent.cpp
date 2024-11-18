// Copyright Al Learning


#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include "AbilitySystem/Abilities/AuraGameplayAbility.h"


void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
}

void UAuraAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for (const TSubclassOf<UGameplayAbility> AbilityClass: StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		if (const UAuraGameplayAbility* AurAbility = Cast<UAuraGameplayAbility> (AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(AurAbility->StartupInputTag);
			GiveAbility(AbilitySpec);
		}
	}
}

void UAuraAbilitySystemComponent::AuraInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) { return; }

	for (FGameplayAbilitySpec& Ability: GetActivatableAbilities())
	{
		if (Ability.DynamicAbilityTags.HasTagExact(InputTag))
		{
			if (!Ability.IsActive())
			{
				TryActivateAbility(Ability.Handle);
			}
		}
	}

	
}

void UAuraAbilitySystemComponent::AuraInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) { return; }

	for (FGameplayAbilitySpec& Ability: GetActivatableAbilities())
	{
		if (Ability.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(Ability);
		}
	}

}


void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                                const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle) const
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	EffectAssetTags.Broadcast(TagContainer);
}



