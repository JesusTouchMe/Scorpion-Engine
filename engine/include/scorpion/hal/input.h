// Copyright 2025 JesusTouchMe

#ifndef SCORPION_INPUT_H
#define SCORPION_INPUT_H 1

#include "scorpion/core/api.h"

#include "scorpion/util/math.h"

namespace scorpion::input {
    enum class MouseButton {
        Left = 0,
        Right = 1,
        Middle = 2,
        Side = 3,
        Extra = 4,
        Forward = 5,
        Back = 6,
    };

    SCORPION_API bool IsMouseButtonPressed(MouseButton button);
    SCORPION_API bool IsMouseButtonDown(MouseButton button);
    SCORPION_API bool IsMouseButtonReleased(MouseButton button);
    SCORPION_API math::Vec2 GetMousePosition();
    SCORPION_API math::Vec2 GetMousePositionDelta();
    SCORPION_API float GetMouseWheel();
}

#endif //SCORPION_INPUT_H