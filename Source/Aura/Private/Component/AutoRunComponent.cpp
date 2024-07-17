// Sean Sanii Nejad

#include "Components/SplineComponent.h"
#include "Component/AutoRunComponent.h"
#include "Player/AuraPlayerController.h"
#include "NavigationPath.h"
#include <NavigationSystem.h>

// Sets default values for this component's properties
UAutoRunComponent::UAutoRunComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
	
}


// Called when the game starts
void UAutoRunComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Hello, from AutoRunComponent::BeginPlay"));
	}
}


// Called every frame
void UAutoRunComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	AutoRun();
	
}

void UAutoRunComponent::AutoRun()
{
	if (!bAutoRunning) return;
	if (APawn* ControlledPawn = Cast<APawn>(GetOwner()))
	{
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);
		ControlledPawn->AddMovementInput(Direction);


		AAuraPlayerController* PlayerController = Cast<AAuraPlayerController>(Cast<APawn>(GetOwner())->GetInstigatorController());

		const float DistanceToDestination = (LocationOnSpline - PlayerController->CachedDestination).Length();
		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
	}
}

void UAutoRunComponent::Run()
{
	if (!bTargeting && !bShiftKeyDown)
	{
		const APawn* ControlledPawn = Cast<APawn>(GetOwner());
		if (FollowTime <= ShortPressedThreshold)
		{
			AAuraPlayerController* PlayerController = Cast<AAuraPlayerController>(Cast<APawn>(GetOwner())->GetInstigatorController());
			if (UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), PlayerController->CachedDestination))
			{
				Spline->ClearSplinePoints();
				for (const FVector& PointLoc : NavPath->PathPoints)
				{
					Spline->AddSplinePoint(PointLoc, ESplineCoordinateSpace::World);
					DrawDebugSphere(GetWorld(), PointLoc, 8.f, 8, FColor::Green, false, 5.f);
				}
				if (NavPath->PathPoints.Num() > 0)
				{
					PlayerController->CachedDestination = NavPath->PathPoints[NavPath->PathPoints.Num() - 1];
					bAutoRunning = true;
				}
			}
		}
		FollowTime = 0.f;
		bTargeting = false;
	}
}
