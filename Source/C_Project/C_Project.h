// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

//쉬운 변수의 Get Set을 위한 매크로
#define PROPERTY_GETTER(propertyName ,type) UFUNCTION(BlueprintGetter) FORCEINLINE type Get##propertyName() const {\
	return propertyName;\
}
//쉬운 변수의 Get Set을 위한 매크로
#define PROPERTY_SETTER(propertyName, type) UFUNCTION(BlueprintSetter) FORCEINLINE void Set##propertyName(type value){\
	propertyName = value;\
 }

