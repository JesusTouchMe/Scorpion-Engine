// Copyright 2025 JesusTouchMe

#include "scorpion/core/actor.h"

#include "scorpion/engine_std/camera.h"
#include "scorpion/engine_std/transform.h"

namespace scorpion::components {
    Camera::Camera(Actor* owner, math::Vec3 position, math::Vec3 target, math::Vec3 up, float fovY, Projection projection)
        : Component(owner)
        , mTransform(nullptr)
        , mPosition(position)
        , mTarget(target)
        , mUp(up)
        , mFovY(fovY)
        , mProjection(projection) {}

    void Camera::onStart() {
        mTransform = getOwner()->getComponent<Transform>();
    }

    void Camera::onUpdate(double dt) {
        if (mTransform == nullptr) return;

        mPosition = mTransform->getPosition();
    }

    math::Vec3 Camera::getPosition() const {
        return mPosition;
    }

    math::Vec3 Camera::getTarget() const {
        return mTarget;
    }

    math::Vec3 Camera::getUp() const {
        return mUp;
    }

    math::Vec3 Camera::getForward() const {
        return (mTarget - mPosition);
    }

    math::Vec3 Camera::getRight() const {
        math::Vec3 forward = this->getForward();
        math::Vec3 up = this->mUp;

        return forward.cross(up);
    }

    float Camera::getFovY() const {
        return mFovY;
    }

    Camera::Projection Camera::getProjection() const {
        return mProjection;
    }

    void Camera::setPosition(math::Vec3 position) {
        mPosition = position;
    }

    void Camera::setTarget(math::Vec3 target) {
        mTarget = target;
    }

    void Camera::setUp(math::Vec3 up) {
        mUp = up;
    }

    void Camera::setFovY(float fovY) {
        mFovY = fovY;
    }

    void Camera::setProjection(Projection projection) {
        mProjection = projection;
    }
}
