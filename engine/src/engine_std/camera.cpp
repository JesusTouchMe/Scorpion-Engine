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

    math::Vec3 Camera::forward() const {
        return (target - position).normalized();
    }

    math::Vec3 Camera::right() const {
        math::Vec3 forward = this->forward();
        math::Vec3 up = this->up.normalized();

        return forward.cross(up).normalized();
    }
}
