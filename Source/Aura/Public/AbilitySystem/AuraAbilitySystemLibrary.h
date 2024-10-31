// Copyright Al Learning

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AuraAbilitySystemLibrary.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintPure, Category="NN_AbilitySystemBlueprintLibrary")
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);
		
};
