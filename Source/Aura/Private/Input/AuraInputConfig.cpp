// Copyright Al Learning


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound)
{
	for (auto AbilityInputAction : AbilityInputActions)
	{
		if (AbilityInputAction.InputTag == InputTag)
		{
			if (AbilityInputAction.InputAction)
			{
				return AbilityInputAction.InputAction;
			}
		}
	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find abilityInputAction for InputTag [%s], on inputConfig [%s]"), *InputTag.ToString(), *GetNameSafe(this));
	}
	return nullptr;
}
