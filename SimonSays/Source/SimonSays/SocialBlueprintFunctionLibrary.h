

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

	UFUNCTION(BlueprintCallable, Category="Share")
	static FString BuildShareGoogleUrl(FString url, FString text);

	UFUNCTION(BlueprintCallable, Category = "Share")
	static FString BuildShareFacebookUrl(FString url);

	UFUNCTION(BlueprintCallable, Category = "Share")
	static FString BuildShareRedditUrl(FString url, FString title);

	UFUNCTION(BlueprintCallable, Category = "Share")
	static FString BuildShareTwitterUrl(FString url, FString text, FString hashtags);

	UFUNCTION(BlueprintCallable, Category = "Share")
	static FString BuildShareTelegramUrl(FString url, FString text);
};
