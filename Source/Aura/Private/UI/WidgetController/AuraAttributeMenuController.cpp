// Copyright Al Learning


#include "UI/WidgetController/AuraAttributeMenuController.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "Aura/AuraGameplayTags.h"

void UAuraAttributeMenuController::BroadcastInitialValues()
{
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
	
	for (auto& Pair: AS->TagsToAttributes)
	{
		FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Pair.Key);
		Info.AttributeValue = Pair.Value().GetNumericValue(AS);
		AttributeInfoDelegate.Broadcast(Info);
	}
}

void UAuraAttributeMenuController::BindCallbacksToDependencies()
{
}
	