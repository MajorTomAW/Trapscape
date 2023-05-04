// Fill out your copyright notice in the Description page of Project Settings.


#include "BPInteractNPC.h"

ABPInteractNPC::ABPInteractNPC()
{
	if(!NPCMesh)
	{
		NPCMesh = CreateDefaultSubobject<USkeletalMeshComponent>("NPC Mesh");
		NPCMesh->SetupAttachment(RootComponent);
	}
}
