// Copyright 2025 JesusTouchMe

#ifndef SCORPION_RENDERER_H
#define SCORPION_RENDERER_H 1

#include "scorpion/core/api.h"

namespace scorpion::render {
    SCORPION_API void InitWindow(int width, int height, const char* title);
    SCORPION_API void CloseWindow();
}

#endif // SCORPION_RENDERER_H
