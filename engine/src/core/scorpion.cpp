// Copyright 2025 JesusTouchMe

#include "scorpion/core/scorpion.h"

#include "scorpion/util/timer.h"

#include <raylib.h>

namespace scorpion {
    struct EngineCore {
        Timer<> updateTimer;
        Timer<> renderTimer;

        HashMap<uint32_t, UniquePtr<Scene>> scenes;
        Scene* activeScene = nullptr;

        Vector<std::function<void(UpdateHookHandle&)>> updateHooks;

        void setTargetFPS(int fps) {
            renderTimer.reset(1.0 / fps);
        }

        void setTargetTPS(int tps) {
            updateTimer.reset(1.0 / tps);
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

        void addUpdateHook(std::function<void(UpdateHookHandle&)> hook) {
            updateHooks.push_back(std::move(hook));
        }

        bool shouldRun() {
            return !WindowShouldClose();
        }

        void tickTimers() {
            updateTimer.tick();
            renderTimer.tick();
        }

        void waitForUpdateOrRender() {
            if (updateTimer.getTarget() == 0.0 && renderTimer.getTarget() == 0.0) return;

            auto now = updateTimer.getCurrentTime();
            auto nextUpdate = updateTimer.getTarget() > 0.0 ? updateTimer.nextDue() : now;
            auto nextRender = renderTimer.getTarget() > 0.0 ? renderTimer.nextDue() : now;

            if (nextUpdate < nextRender) {
                updateTimer.wait();
            } else {
                renderTimer.wait();
            }
        }

        void update() {
            auto tick = [this](double dt) {
                for (auto it = updateHooks.begin(); it != updateHooks.end();) {
                    UpdateHookHandle handle;
                    (*it)(handle);

                    if (handle.mUnregistered) {
                        it = updateHooks.erase(it);
                    } else {
                        ++it;
                    }
                }

                if (activeScene != nullptr) activeScene->update(dt);
            };

            if (updateTimer.getTarget() == 0.0) {
                tick(updateTimer.getDelta());
            } else if (updateTimer.getCurrentTime() >= updateTimer.nextDue()) {
                tick(updateTimer.getTarget());
            }
        }

        void render() {
            auto tick = [this] {
                if (activeScene != nullptr) activeScene->render();
            };

            // each, i know this can be turned into a or, but we tryna match with update()
            if (renderTimer.getTarget() == 0.0) {
                tick();
            } else if (renderTimer.getCurrentTime() >= renderTimer.nextDue()) {
                tick();
            }
        }
    };

    static EngineCore core;

    void UpdateHookHandle::unregister() {
        mUnregistered = true;
    }

    void Run() {
        while (ShouldRun()) {
            TickTimers();
            WaitForUpdateOrRender();
            Update();
            Render();
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

    void AddUpdateHook(std::function<void(UpdateHookHandle&)> hook) {
        core.addUpdateHook(std::move(hook));
    }

    bool ShouldRun() {
        return core.shouldRun();
    }

    void TickTimers() {
        core.tickTimers();
    }

    void WaitForUpdateOrRender() {
        core.waitForUpdateOrRender();
    }

    void Update() {
        core.update();
    }

    void Render() {
        core.render();
    }
}
