// Copyright 2025 JesusTouchMe

#include "scorpion/render/renderer.h"

#include <raylib.h>

namespace scorpion::render {
    void InitWindow(int width, int height, const char* title) {
        ::InitWindow(width, height, title);
        ::SetExitKey(KEY_NULL);
        ::SetTargetFPS(0);
    }

    void CloseWindow() {
        ::CloseWindow();
    }
}
