// Copyright Al Learning


#include "Character/AuraEnemy.h"

AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCustomDepthStencilValue(STENCIL_VALUE);
	Weapon->SetCustomDepthStencilValue(STENCIL_VALUE);
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}	

void AAuraEnemy::HighlightActor()
{
	isHighlighted = true;
	GetMesh()->SetRenderCustomDepth(true);
	Weapon->SetRenderCustomDepth(true);
}

void AAuraEnemy::UnhighlightActor()
{
	isHighlighted = false;
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}
