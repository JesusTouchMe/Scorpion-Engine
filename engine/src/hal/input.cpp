// Copyright 2025 JesusTouchMe

#include "scorpion/hal/input.h"

#include <raylib.h>

namespace scorpion::input {
    bool IsMouseButtonPressed(MouseButton button) {
        return ::IsMouseButtonPressed(static_cast<int>(button));
    }

    bool IsMouseButtonDown(MouseButton button) {
        return ::IsMouseButtonDown(static_cast<int>(button));
    }

    bool IsMouseButtonReleased(MouseButton button) {
        return ::IsMouseButtonReleased(static_cast<int>(button));
    }

    math::Vec2 GetMousePosition() {
        Vector2 rlVec = ::GetMousePosition();
        return {rlVec.x, rlVec.y};
    }

    math::Vec2 GetMousePositionDelta() {
        Vector2 rlVec = ::GetMouseDelta();
        return {rlVec.x, rlVec.y};
    }

    float GetMouseWheel() {
        return ::GetMouseWheelMove();
    }
}
