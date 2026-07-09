#pragma once

#include "CoreMinimal.h"
#include <utility>

#if !UE_BUILD_SHIPPING
	#define SCREEN_LOG(Time, Color, Format, ...) \
		DebugUtility::ScreenMessage(Time, Color, Format, ##__VA_ARGS__);
#else
	#define SCREEN_LOG(Time, Color, Format, ...)
#endif

class HELICONUNREAL_API DebugUtility
{
public:
	DebugUtility();
	~DebugUtility();
	
	/*
	 * Draws a debug line, Arguments after End are forwarded to DrawDebugLine(). 
	 */
	template<typename... Args>
	static auto QuickLine(UWorld* World, const FVector& Start, const FVector& End, Args&&... args) -> void
	{
#if WITH_EDITOR
		if (World)
		{
			DrawDebugLine(World, Start, End, std::forward<Args>(args)...);
		}
#endif
	}
	/*
	 * Prints a formatted string both to the screen and output log
	 */
	template<typename... Args>
	static auto ScreenMessage(const float DisplayTime, const FColor& Color, const FString& Format, Args&&... args) -> void
	{
		if constexpr (!UE_BUILD_SHIPPING)
		{
			if (GEngine)
			{
				const TArray<FStringFormatArg> FormatArgs =
				{
					FStringFormatArg(ToLogString(std::forward<Args>(args)))...
				};

				const FString Msg = FString::Format(*Format, FormatArgs);

				GEngine->AddOnScreenDebugMessage(-1, DisplayTime, Color, Msg);

				UE_LOG(LogTemp, Warning, TEXT("[DebugUtility] %s"), *Msg);
			}
		}
	}
	
	template<typename T>
	static FORCEINLINE auto ToLogString(const T& Value) -> FString
	{
		if constexpr (std::is_same_v<std::decay_t<T>, FText>)
		{
			return Value.ToString();
		}
		else if constexpr (std::is_same_v<std::decay_t<T>, FName>)
		{
			return Value.ToString();
		}
		else
		{
			return LexToString(Value);
		}
	}
};

//SCREEN_LOG(3, TEXT("STRING {0}", string )

