// Copyright 2025 JesusTouchMe

#include "scorpion/engine_std/transform.h"

namespace scorpion::components {
    math::Matrix4 Transform::getMatrix() const {
        math::Matrix4 t = math::Matrix4::translation(position);
        math::Matrix4 r = math::Matrix4::rotation(rotation);
        math::Matrix4 s = math::Matrix4::scale(size);
        return t * r * s;
    }
}