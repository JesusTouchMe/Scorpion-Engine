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

        void setTargetFPS(int fps) {
            targetFPS = fps;
            renderInterval = 1.0 / fps;
        }

        void setTargetTPS(int tps) {
            targetTPS = tps;
            updateInterval = 1.0 / tps;
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
            auto tick = [] {
                //TODO: run engine tick
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
            BeginDrawing();
            ClearBackground(BLACK);

            //TODO: draw frame

            EndDrawing();
        }
    };

    static EngineCore core;

    void Run() {
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
