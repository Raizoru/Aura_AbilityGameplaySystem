// Sean Sanii Nejad


#include "Component/AutoRunComponent.h"

// Sets default values for this component's properties
UAutoRunComponent::UAutoRunComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
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

	
}

