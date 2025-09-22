// Copyright 2025 JesusTouchMe

#include "scorpion/engine_std/transform.h"

namespace scorpion::components {
    Transform::Transform(Actor* owner, math::Vec3 position, math::Vec3 size, math::Quat rotation)
        : Component(owner)
        , mPosition(position)
        , mSize(size)
        , mRotation(rotation) {}

    math::Matrix4 Transform::getMatrix() const {
        math::Matrix4 t = math::Matrix4::translation(mPosition);
        math::Matrix4 r = math::Matrix4::rotation(mRotation);
        math::Matrix4 s = math::Matrix4::scale(mSize);
        return t * r * s;
    }

    math::Vec3 Transform::getPosition() const {
        return mPosition;
    }

    math::Vec3 Transform::getSize() const {
        return mSize;
    }

    math::Quat Transform::getRotation() const {
        return mRotation;
    }

    void Transform::setPosition(math::Vec3 position) {
        mPosition = position;
    }

    void Transform::setSize(math::Vec3 size) {
        mSize = size;
    }

    void Transform::setRotation(math::Quat rotation) {
        mRotation = rotation;
    }
}
