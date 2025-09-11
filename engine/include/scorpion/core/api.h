// Copyright 2025 JesusTouchMe

#ifndef SCORPION_API_H
#define SCORPION_API_H 1

#ifdef PLATFORM_WINDOWS
    #ifdef SCORPION_BUILD
        #define SCORPION_API __declspec(dllexport)
    #else
        #define SCORPION_API __declspec(dllimport)
    #endif
#else
    #define SCORPION_API __attribute__((visibility("default")))
#endif

#endif // SCORPION_API_H
