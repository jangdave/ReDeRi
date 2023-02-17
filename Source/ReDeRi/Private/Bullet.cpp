// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "RedPlayer.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("sphereComp"));
	SetRootComponent(sphereComp);
	sphereComp->SetSphereRadius(5);
	sphereComp->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	meshComp->SetupAttachment(sphereComp);
	meshComp->SetRelativeScale3D(FVector(0.5f));
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Game/Asset/prop/Bullet.Bullet'"));
	if (tempMesh.Succeeded())
	{
		meshComp->SetStaticMesh(tempMesh.Object);

		meshComp->SetRelativeRotation(FRotator(0, -90.0f, 0));
	}

	movementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("movementComp"));
	movementComp->SetUpdatedComponent(sphereComp);
	movementComp->InitialSpeed = 2000.0f;
	movementComp->MaxSpeed = 2000.0f;
	movementComp->ProjectileGravityScale = 0.2f;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	// 총알이 플레이어에게 맞았을 때
	if (OtherActor->IsA(ARedPlayer::StaticClass()))
	{
		// 플레이어 타입으로 캐스팅
		ARedPlayer* player = Cast<ARedPlayer>(OtherActor);

		// 만약 닿은게 player라면 OnDamage함수를 실행하고 데미지를 넘겨준다.
		if (player)
		{
			player->OnDamage(Damage);
			UE_LOG(LogTemp, Warning, TEXT("Hittest"));
		}
		// 총알 파괴
		Destroy();
	}
	else
	{
		// 총알 사운드 재생
		UGameplayStatics::PlaySoundAtLocation(this, BulletWhipSound, GetActorLocation());
	}
}

