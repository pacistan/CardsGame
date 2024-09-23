#pragma once

// Declare the log category 
CARDGAME_ICAN_5JV_1_API DECLARE_LOG_CATEGORY_EXTERN(LogCard, Log, All);
CARDGAME_ICAN_5JV_1_API DECLARE_LOG_CATEGORY_EXTERN(LogDebugCard, Log, All);

// log Macro
#define DEBUG_ERROR(Format,...) UE_LOG(LogDebugCard,Error,Format,__VA_ARGS__)
#define DEBUG_WARNING(Format,...) UE_LOG(LogDebugCard,Warning,Format,__VA_ARGS__)
#define DEBUG_LOG(Format,...) UE_LOG(LogDebugCard,Log,Format,__VA_ARGS__)
#define DEBUG_ERROR_CATEGORY(Category, Format,...) UE_LOG(Category,Error,Format,__VA_ARGS__)
#define DEBUG_WARNING_CATEGORY(Category,Format,...) UE_LOG(Category,Warning,Format,__VA_ARGS__)
#define DEBUG_LOG_CATEGORY(Category,Format,...) UE_LOG(Category,Log,Format,__VA_ARGS__)
#define LOG_ERROR(Format,...) UE_LOG(LogCard,Error,Format,__VA_ARGS__)
#define LOG_WARNING(Format,...) UE_LOG(LogCard,Warning,Format,__VA_ARGS__)
#define LOG_LOG(Format,...) UE_LOG(LogCard,Log,Format,__VA_ARGS__)

// log Screen Macro
#define DEBUG_LOG_SCREEN(Key, DisplayTime, Color, Format, ...) if(GEngine){\
GEngine->AddOnScreenDebugMessage(Key, DisplayTime, Color, FString::Printf(Format, __VA_ARGS__));\
}

#define DEBUG_LOG_SCREEN_SIMPLE(Format, ...) if(GEngine){\
GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(Format, __VA_ARGS__));\
}