// Copyright Al Learning


#include "UI/WidgetController/AuraAttributeMenuController.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "Aura/AuraGameplayTags.h"

void UAuraAttributeMenuController::BroadcastInitialValues()
{
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
	check (AS);
	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(FAuraGameplayTags::Get().Attributes_Primary_Strength);
	Info.AttributeValue = AS->GetStrength();
	AttributeInfoDelegate.Broadcast(Info);
	Info = AttributeInfo->FindAttributeInfoForTag(FAuraGameplayTags::Get().Attributes_Primary_Intelligence);
	Info.AttributeValue = AS->GetIntelligence();
	AttributeInfoDelegate.Broadcast(Info);
}

void UAuraAttributeMenuController::BindCallbacksToDependencies()
{
}
	