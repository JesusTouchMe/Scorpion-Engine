// Copyright 2025 JesusTouchMe

#include "scorpion/core/actor.h"

#include "scorpion/engine_std/camera.h"
#include "scorpion/engine_std/transform.h"

namespace scorpion::components {
    void Camera::syncWithTransform() {
        Transform* transform = getOwner()->getComponent<Transform>();
        if (transform == nullptr) return;

        position = transform->position;
    }
}
