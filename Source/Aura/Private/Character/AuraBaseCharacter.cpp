// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraBaseCharacter.h"

AAuraBaseCharacter::AAuraBaseCharacter()
{

	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAuraBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


