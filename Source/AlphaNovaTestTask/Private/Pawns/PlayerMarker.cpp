#include "Pawns/PlayerMarker.h"
#include "Camera/CameraComponent.h"
#include "Components/PhysicsMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Helpers/MaterialInstanceDynamicHelper.h"
#include "InputActionValue.h"
#include "Interfaces/Dyeable.h"

DEFINE_LOG_CATEGORY(LogPlayerMarker);

APlayerMarker::APlayerMarker()
{
	PrimaryActorTick.bCanEverTick = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	Mesh->SetSimulatePhysics(true);

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	CollisionSphere->SetupAttachment(RootComponent);
	
	PhysicsMovement = CreateDefaultSubobject<UPhysicsMovementComponent>(TEXT("PhysicsMovement"));

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void APlayerMarker::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = GetController<APlayerController>();
	if (IsValid(PlayerController))
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (IsValid(Subsystem))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	MaterialInstanceDynamic = UMaterialInstanceDynamicHelper::CreateMaterialInstanceOnMesh(Mesh);
	if (IsValid(MaterialInstanceDynamic))
	{
		UMaterialInstanceDynamicHelper::SetMaterialInstanceColor(MaterialInstanceDynamic, MarkColor);
	}
	else
	{
		UE_LOG(LogPlayerMarker, Warning, TEXT("%hs: Can't create material dynamic instance!"), __FUNCTION__);
	}
	
	// We're doing this on overlap collision because a hit event generation during physics simulation isn't the optimal way
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnCollisionSphereOverlap);
}

void APlayerMarker::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (IsValid(EnhancedInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
	}
}

void APlayerMarker::Move(const FInputActionValue& Value)
{
	FVector2D MoveVector = Value.Get<FVector2D>();

	if (IsValid(Controller))
	{
		const FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		if (IsValid(PhysicsMovement))
		{
			FVector ForwardMoveVector = ForwardDirection * MoveVector.Y;
			FVector RightMoveVector = RightDirection * MoveVector.X;
			PhysicsMovement->MoveByForce(ForwardMoveVector);
			PhysicsMovement->MoveByForce(RightMoveVector);
		}
	}
}

void APlayerMarker::Look(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();

	if (IsValid(Controller))
	{
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(LookVector.Y);
	}
}

void APlayerMarker::OnCollisionSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IDyeable* Dyeable = Cast<IDyeable>(OtherActor);
	if (!Dyeable)
	{
		return;
	}

	// The player marker should always dye other targets if they are not already dyed
	if (!Dyeable->IsDyed())
	{
		Dyeable->Dye(MarkColor);
	}
}
