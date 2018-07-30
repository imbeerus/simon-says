

#include "SocialBlueprintFunctionLibrary.h"

FString USocialBlueprintFunctionLibrary::BuildShareGoogleUrl(FString url, FString text)
{
	FString BaseUrl = "https://plus.google.com/share?";
	BaseUrl.Append("url=").Append(url);
	BaseUrl.Append("&text=").Append(text);
	return BaseUrl;
}

FString USocialBlueprintFunctionLibrary::BuildShareFacebookUrl(FString url)
{
	FString BaseUrl = "https://www.facebook.com/sharer.php?";
	BaseUrl.Append("u=").Append(url);
	return BaseUrl;
}

FString USocialBlueprintFunctionLibrary::BuildShareRedditUrl(FString url, FString title)
{
	FString BaseUrl = "https://reddit.com/submit?";
	BaseUrl.Append("url=").Append(url);
	BaseUrl.Append("&title=").Append(title);
	return BaseUrl;
}

FString USocialBlueprintFunctionLibrary::BuildShareTwitterUrl(FString url, FString text, FString hashtags)
{
	FString BaseUrl = "https://twitter.com/intent/tweet?";
	BaseUrl.Append("url=").Append(url);
	BaseUrl.Append("&text=").Append(text);
	BaseUrl.Append("&hashtags=").Append(hashtags);
	return BaseUrl;
}

FString USocialBlueprintFunctionLibrary::BuildShareTelegramUrl(FString url, FString text)
{
	FString BaseUrl = "https://t.me/share/url?";
	BaseUrl.Append("url=").Append(url);
	BaseUrl.Append("&text=").Append(url);
	return BaseUrl;
}