// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PhotonTestProjectDataAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class PHOTONTESTPROJECT_API UPhotonTestProjectDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString AppID;	
};
