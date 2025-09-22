// Copyright 2025 JesusTouchMe

#ifndef SCORPION_H
#define SCORPION_H 1

#include "scorpion/core/scene.h"

#include <functional>

namespace scorpion {
    class UpdateHookHandle {
    friend struct EngineCore;
    public:
        void unregister();

    private:
        bool mUnregistered = false;
    };

    SCORPION_API void Run();

    SCORPION_API void SetTargetFPS(int fps);
    SCORPION_API void SetTargetTPS(int tps);

    SCORPION_API Scene* CreateScene(uint32_t id);
    SCORPION_API Scene* GetActiveScene();
    SCORPION_API void SetActiveScene(uint32_t id);

    SCORPION_API Actor* CreateActor();
    SCORPION_API void DestroyActor(Actor* actor);

    // The following functions are exposed in case the user needs more control over the game loop

    SCORPION_API void AddUpdateHook(std::function<void(UpdateHookHandle&)> hook);

    SCORPION_API bool ShouldRun();

    SCORPION_API void TickTimers();
    SCORPION_API void WaitForUpdateOrRender();

    SCORPION_API void Update();
    SCORPION_API void Render();
}

#endif // SCORPION_H
