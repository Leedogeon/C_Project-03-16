// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DragWidget.generated.h"

/**
 * 드래그 가능한 위젯을 정의합니다.
 */
UCLASS()
class C_PROJECT_API UDragWidget : public UUserWidget
{
	GENERATED_BODY()


protected:
	//드래그 시 필요한 정보를 저장할 오퍼레이터
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCommonDragDropOperation> CommonDragDropOperationObject;
	//드래그 시 드래그중인 위젯을 표현하기 위해 사용할 위젯. 굳이 없어도 괜찮습니다.
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UDragShadowWidget> DragShadowWidgetObject;
	//위 클래스 정보로 생성된 위젯을 저장할 변수
	UPROPERTY()
		class UDragShadowWidget* DragShadowWidget;

	UPROPERTY()
		FVector2D DragOffset;

	virtual void NativeConstruct() override;
	//드래그가 감지되면 호출됩니다.
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	//마우스 버튼을 누르면 호출됩니다.
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;


};
