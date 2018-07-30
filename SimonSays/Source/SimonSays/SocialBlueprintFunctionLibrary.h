

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SocialBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class SIMONSAYS_API USocialBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	static FString BuildShareGoogleUrl(FString url, FString text);

	UFUNCTION(BlueprintCallable)
	static FString BuildShareFacebookUrl(FString url);

	UFUNCTION(BlueprintCallable)
	static FString BuildShareRedditUrl(FString url, FString title);

	UFUNCTION(BlueprintCallable)
	static FString BuildShareTwitterUrl(FString url, FString text, FString via, FString hashtags);

	UFUNCTION(BlueprintCallable)
	static FString BuildShareTelegramUrl(FString url, FString text);
};
