// Fill out your copyright notice in the Description page of Project Settings.

#include "FWBTService_GetPlayerPosition.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "FWUtilities.h"
#include "FWPlayerCharacterBase.h"
#include "NavigationSystem.h"

void UFWBTService_GetPlayerPosition::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AFWPlayerCharacterBase* PlayerCharacter = UFWUtilities::GetPlayerCharacter(this);
	if (PlayerCharacter)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(PlayerBlackboardKey.SelectedKeyName, PlayerCharacter);
		FVector PlayerPosition = PlayerCharacter->GetActorLocation();
		FVector TraceStart = PlayerPosition + FVector(0.f, 0.f, TraceCheckOffsetZ);
		FVector TraceEnd = TraceStart - FVector::UpVector * TraceDownDistance;
		FHitResult Hit;
		FCollisionObjectQueryParams ObjectQueryParams;
		ObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
		if (GetWorld()->LineTraceSingleByObjectType(Hit, TraceStart, TraceEnd, ObjectQueryParams))
		{
			PlayerPosition = Hit.ImpactPoint;
		}
		FNavLocation ProjectedLocation;
		if (UNavigationSystemV1::GetCurrent(this)->ProjectPointToNavigation(PlayerPosition, ProjectedLocation, QueryExtent, NULL, NULL))
		{
			PlayerPosition = ProjectedLocation.Location;
		}
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, PlayerPosition);
	}
}
