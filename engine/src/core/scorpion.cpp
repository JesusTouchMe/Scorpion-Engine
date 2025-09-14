// Copyright 2025 JesusTouchMe

#include "scorpion/core/scorpion.h"

#include "scorpion/util/timer.h"

#include <raylib.h>

namespace scorpion {
    struct EngineCore {
        int targetFPS;
        int targetTPS;

        double renderInterval;
        double updateInterval;

        Timer<> updateTimer;
        Timer<> renderTimer;

        HashMap<uint32_t, UniquePtr<Scene>> scenes;
        Scene* activeScene;

        void setTargetFPS(int fps) {
            targetFPS = fps;
            renderInterval = 1.0 / fps;
        }

        void setTargetTPS(int tps) {
            targetTPS = tps;
            updateInterval = 1.0 / tps;
        }

        Scene* createScene(uint32_t id) {
            UniquePtr<Scene> scene = MakeUnique<Scene>();
            Scene* ptr = scene.get();

            scenes[id] = std::move(scene);

            return ptr;
        }

        void setActiveScene(uint32_t id) {
            activeScene = scenes.at(id).get();
        }

        bool shouldRun() {
            return !WindowShouldClose();
        }

        bool shouldUpdate() {
            if (targetTPS == 0) return true;

            updateTimer.update(updateTimer.deltaTime());
            return updateTimer.getAccumulator() >= updateInterval;
        }

        bool shouldRender() {
            if (targetFPS == 0) return true;

            renderTimer.update(renderTimer.deltaTime());
            if (renderTimer.getAccumulator() >= renderInterval) {
                renderTimer.update(-renderInterval);
                return true;
            }
            return false;
        }

        void update() {
            auto tick = [this] {
                if (activeScene != nullptr) activeScene->update(updateInterval);
            };

            if (targetTPS == 0) {
                tick();
                return;
            }

            while (updateTimer.getAccumulator() >= updateInterval) {
                tick();

                updateTimer.update(-updateInterval);
            }
        }

        void render() {
            if (activeScene != nullptr) activeScene->render();
        }
    };

    static EngineCore core;

    void Run() {
        //TODO: make a function that blocks until the next thing (update/render) should run
        while (ShouldRun()) {
            if (ShouldUpdate()) Update();
            if (ShouldRender()) Render();
        }
    }

    void SetTargetFPS(int fps) {
        core.setTargetFPS(fps);
    }

    void SetTargetTPS(int tps) {
        core.setTargetTPS(tps);
    }

    Scene* CreateScene(uint32_t id) {
        return core.createScene(id);
    }

    Scene* GetActiveScene() {
        return core.activeScene;
    }

    void SetActiveScene(uint32_t id) {
        core.setActiveScene(id);
    }

    Actor* CreateActor() {
        return core.activeScene->addActor<Actor>();
    }

    void DestroyActor(Actor* actor) {
        actor->getScene()->removeActor(actor);
    }

    bool ShouldRun() {
        return core.shouldRun();
    }

    bool ShouldUpdate() {
        return core.shouldUpdate();
    }

    void Update() {
        core.update();
    }

    bool ShouldRender() {
        return core.shouldRender();
    }

    void Render() {
        core.render();
    }
}
