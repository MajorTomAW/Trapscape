// Fill out your copyright notice in the Description page of Project Settings.


#include "BPDefense.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"

ABPDefense::ABPDefense()
{
	if(!AIPerceptionComponent)
	{
		AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>("AI Perception Stimuli Source");
	}
}
