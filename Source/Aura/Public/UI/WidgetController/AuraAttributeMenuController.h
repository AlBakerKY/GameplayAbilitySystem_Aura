// Copyright Al Learning

#pragma once

#include "CoreMinimal.h"
#include "AuraWidgetController.h"
#include "AuraAttributeMenuController.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraAttributeMenuController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
};
