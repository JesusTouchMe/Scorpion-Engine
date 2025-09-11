// Copyright 2025 JesusTouchMe

#ifndef SCORPION_H
#define SCORPION_H 1

#include "scorpion/core/api.h"

namespace scorpion {
    SCORPION_API void Run();

    SCORPION_API void SetTargetFPS(int fps);
    SCORPION_API void SetTargetTPS(int tps);

    // The following functions are exposed in case the user needs specific stuff in the game loop

    SCORPION_API bool ShouldRun();

    SCORPION_API bool ShouldUpdate();
    SCORPION_API void Update();
    SCORPION_API bool ShouldRender();
    SCORPION_API void Render();
}

#endif // SCORPION_H
