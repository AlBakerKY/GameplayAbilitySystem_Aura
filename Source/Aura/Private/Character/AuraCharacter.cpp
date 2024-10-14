// Copyright Al Learning


#include "Character/AuraCharacter.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerState.h"
#include "AbilitySystemComponent.h"
#include "UI/HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityActorInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilityActorInfo();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);
	Cast<UAuraAbilitySystemComponent>(AuraPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();
	AAuraHUD* HUD = Cast<AAuraHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (HUD != nullptr)
	{
		HUD->InitOverlay(Cast<APlayerController>(GetController()), AuraPlayerState, AbilitySystemComponent, AttributeSet);
	}
	InitializePrimaryAttributes();	
}

void AAuraCharacter::InitializePrimaryAttributes() const
{
	check(IsValid(AbilitySystemComponent));
	check(DefaultPrimaryAttributes);
	FGameplayEffectSpecHandle PrimarySpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(DefaultPrimaryAttributes, 1.f, GetAbilitySystemComponent()->MakeEffectContext());
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*PrimarySpecHandle.Data.Get(), GetAbilitySystemComponent());

	check(DefaultSecondaryAttributes);
	FGameplayEffectSpecHandle SecondarySpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(DefaultSecondaryAttributes, 1.f, GetAbilitySystemComponent()->MakeEffectContext());
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SecondarySpecHandle.Data.Get(), GetAbilitySystemComponent());
	
}
