# Debug Utility Header #

## Overview ##

The Debug Utility header file consists of a C++ class with static templated methods for debugging in code. Unreal has it's UE_LOG that strips out terminal logs in a shipping build but for on screen debugging there is no macro. This utility solves that problem. 

## Private Methods ## 

### ToLogString ### 
``` template<typename T>
	static FORCEINLINE auto ToLogString(const T& Value) -> FString 
```
ToLogString is a templated function that takes in any possible value and evalutes if the argument is a FText, FName and returns their toString methods or if not calls lexToString to make sure that the value is a FString

	