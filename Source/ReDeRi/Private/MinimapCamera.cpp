// Fill out your copyright notice in the Description page of Project Settings.


#include "MinimapCamera.h"
#include "Kismet/GameplayStatics.h"

AMinimapCamera::AMinimapCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	SetActorLocationAndRotation(FVector(0, 0, 480.0f), FRotator(-90.0f, 0, 0));

	//ECameraProjectionMode::Orthographic;
}

void AMinimapCamera::BeginPlay()
{
	Super::BeginPlay();

}

void AMinimapCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto player = (UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (player != nullptr)
	{
		FVector loc = FVector(player->GetActorLocation().X, player->GetActorLocation().Y, 480.0f);
		SetActorLocation(loc);
	}
	//FVector loc = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}