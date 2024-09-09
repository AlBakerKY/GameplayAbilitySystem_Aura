// Copyright Al Learning


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet* AttributeSetCasted = CastChecked<UAuraAttributeSet>(AttributeSet);
		OnHealthChanged.Broadcast(AttributeSetCasted->GetHealth());
		OnMaxHealthChanged.Broadcast(AttributeSetCasted->GetMaxHealth());
}
