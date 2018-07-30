

#include "UtilsFunctionLibrary.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "Classes/GameFramework/PlayerController.h"

bool UUtilsFunctionLibrary::IsMobilePlatform()
{
	FString Platform = UGameplayStatics::GetPlatformName();
	return Platform.Equals("Android") || Platform.Equals("IOS");
}