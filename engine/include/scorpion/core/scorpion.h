// Copyright 2025 JesusTouchMe

#ifndef SCORPION_H
#define SCORPION_H 1

#include "scorpion/core/scene.h"

namespace scorpion {
    SCORPION_API void Run();

    SCORPION_API void SetTargetFPS(int fps);
    SCORPION_API void SetTargetTPS(int tps);

    SCORPION_API Scene* CreateScene(uint32_t id);
    SCORPION_API Scene* GetActiveScene();
    SCORPION_API void SetActiveScene(uint32_t id);

    SCORPION_API Actor* CreateActor();
    SCORPION_API void DestroyActor(Actor* actor);

    // The following functions are exposed in case the user needs specific stuff in the game loop

    SCORPION_API bool ShouldRun();

    SCORPION_API bool ShouldUpdate();
    SCORPION_API void Update();
    SCORPION_API bool ShouldRender();
    SCORPION_API void Render();
}

#endif // SCORPION_H
