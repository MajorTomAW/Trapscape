#include "BPPlayerBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"

ABPPlayerBase::ABPPlayerBase()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->MaxWalkSpeed = PlayerMovementInfo.WalkSpeed;
	GetCharacterMovement()->AirControl = 1.0f;
	GetCharacterMovement()->GravityScale = 1.2;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 520.0f, 0.0f);

	if (!ThirdPersonSpringarm)
	{
		ThirdPersonSpringarm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
		ThirdPersonSpringarm->SetupAttachment(RootComponent);
		ThirdPersonSpringarm->TargetArmLength = MinSpringArmLength;
		ThirdPersonSpringarm->bUsePawnControlRotation = true;
		ThirdPersonSpringarm->bInheritPitch = true;
		ThirdPersonSpringarm->bInheritRoll = false;
		ThirdPersonSpringarm->bInheritYaw = true;
		ThirdPersonSpringarm->bEnableCameraLag = true;
		ThirdPersonSpringarm->CameraLagSpeed = 12.0f;
	}
	if (!ThirdPersonCam)
	{
		ThirdPersonCam = CreateDefaultSubobject<UCameraComponent>("ThirdPersonCam");
		ThirdPersonCam->SetupAttachment(ThirdPersonSpringarm);
	}
	if(!InteractComponent)
	{
		InteractComponent = CreateDefaultSubobject<UACInteractComponent>("Interact Component");
	}
}

void ABPPlayerBase::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = PlayerMovementInfo.WalkSpeed;
	if(APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}
	InteractComponent->StartScanning();
}

void ABPPlayerBase::PlayerMove(const FInputActionValue& Axis)
{
	if(PlayerMovementInfo.bCanMove)
	{
		const FVector2D MovementVector = Axis.Get<FVector2D>();
		FRotator YawRotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);
		FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(RightVector, MovementVector.X);
		AddMovementInput(ForwardVector, MovementVector.Y);

		if(MovementVector.Y <= 0.0f) SprintSwitch(false);
	}
}

void ABPPlayerBase::PlayerMouse(const FInputActionValue& Axis)
{
	if(PlayerMovementInfo.bCanRotate)
	{
		const FVector2D MouseVector = Axis.Get<FVector2D>();
		AddControllerYawInput(MouseVector.X * PlayerMovementInfo.MouseSensitivity);
		AddControllerPitchInput(MouseVector.Y * -PlayerMovementInfo.MouseSensitivity);

		//Change Spring Arm Length
		const float ControllerPitch = Controller->GetControlRotation().Pitch;
		float NormControllerPitch = ControllerPitch;
		if (ControllerPitch < 270.0f)
		{
			NormControllerPitch = ControllerPitch + 360.0f;
		}
		NormControllerPitch = NormControllerPitch - 270.0f;
		ThirdPersonSpringarm->TargetArmLength = FMath::Lerp(MaxSpringArmlength, MinSpringArmLength, NormControllerPitch / 90.0f);
	}
}

void ABPPlayerBase::PlayerJump()
{
	if(PlayerMovementInfo.bCanJump)
	{
		ACharacter::Jump();
	}
}

void ABPPlayerBase::PlayerSprint()
{
	SprintSwitch(true);
}

void ABPPlayerBase::StartInteracting()
{
	InteractComponent->StartInteracting();
}

void ABPPlayerBase::StopInteracting()
{
	InteractComponent->StopInteracting();
}

void ABPPlayerBase::SprintSwitch(bool bSprintState)
{
	if(!HasAuthority())
	{
		sToggleSprint(bSprintState);
	}
	GetCharacterMovement()->MaxWalkSpeed = bSprintState ? PlayerMovementInfo.SprintSpeed : PlayerMovementInfo.WalkSpeed;
}

void ABPPlayerBase::sToggleSprint_Implementation(bool bSprintState)
{
	SprintSwitch(bSprintState);
}

void ABPPlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABPPlayerBase::PlayerMove);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ABPPlayerBase::PlayerMove);
		EnhancedInputComponent->BindAction(MouseAction, ETriggerEvent::Triggered, this, &ABPPlayerBase::PlayerMouse);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ABPPlayerBase::PlayerJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &ABPPlayerBase::PlayerSprint);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ABPPlayerBase::StartInteracting);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &ABPPlayerBase::StopInteracting);
	}
}

void ABPPlayerBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABPPlayerBase, PlayerMovementInfo);
}
