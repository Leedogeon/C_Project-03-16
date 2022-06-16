// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "CommonDragDropOperation.generated.h"

/**
 * 
 */
UCLASS()
class C_PROJECT_API UCommonDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:
	//���� �巡���� ���� ����.
	UPROPERTY()
		class UUserWidget* DraggedWidget;
	UPROPERTY()
		FVector2D DragOffset;

};
