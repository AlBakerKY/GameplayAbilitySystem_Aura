// Copyright Al Learning


#include "UI/WidgetController/AuraWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"

void UAuraWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UAuraWidgetController::BroadcastInitialValues()
{
	// empty for base class
}

void UAuraWidgetController::BindCallbacksToDependencies()
{
	// empty for base class
}
