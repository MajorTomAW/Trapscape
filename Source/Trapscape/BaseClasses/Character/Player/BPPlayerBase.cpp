#include "BPPlayerBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "GameFramework/CharacterMovementComponent.h"

ABPPlayerBase::ABPPlayerBase()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->MaxWalkSpeed = 640.0f;
	GetCharacterMovement()->AirControl = 1.0f;
	GetCharacterMovement()->GravityScale = 1.2;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

	if (!ThirdPersonSpringarm)
	{
		ThirdPersonSpringarm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
		ThirdPersonSpringarm->SetupAttachment(RootComponent);
		ThirdPersonSpringarm->TargetArmLength = 1480.0f;
		ThirdPersonSpringarm->SetRelativeRotation(FRotator(282.0f, 0.0f, 0.0f));
		ThirdPersonSpringarm->bInheritPitch = false;
		ThirdPersonSpringarm->bInheritRoll = false;
		ThirdPersonSpringarm->bInheritYaw = false;
		ThirdPersonSpringarm->bEnableCameraLag = true;
		ThirdPersonSpringarm->CameraLagSpeed = 12.0f;
	}
	if (!ThirdPersonCam)
	{
		ThirdPersonCam = CreateDefaultSubobject<UCameraComponent>("ThirdPersonCam");
		ThirdPersonCam->SetupAttachment(ThirdPersonSpringarm);
	}
}

void ABPPlayerBase::BeginPlay()
{
	Super::BeginPlay();
	if(APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}
}

void ABPPlayerBase::PlayerMove(const FInputActionValue& Axis)
{
	const FVector2D MovementVector = Axis.Get<FVector2D>();
	AddMovementInput(FVector(0.0f, 1.0f, 0.0f), MovementVector.X);
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), MovementVector.Y);
}

void ABPPlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABPPlayerBase::PlayerMove);
	}
}

void ABPPlayerBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}
