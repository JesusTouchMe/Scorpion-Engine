// Copyright 2025 JesusTouchMe

#include "scorpion/engine_std/physics_body.h"

#include "scorpion/core/actor.h"

namespace scorpion::components {
    const math::Vec3 PhysicsBody::gravity = {0, -9.81, 0};

    PhysicsBody::PhysicsBody(Actor* owner, float mass, bool gravity, bool kinematic)
        : Component(owner)
        , mTransform(nullptr)
        , mMass(mass)
        , mGravity(gravity)
        , mKinematic(kinematic) {}

    void PhysicsBody::onStart() {
        mTransform = getOwner()->getComponent<Transform>();
    }

    void PhysicsBody::onUpdate(double dt) {
        if (mKinematic) return;

        if (mGravity) {
            mForceAccumulator += gravity * mMass;
        }

        mLinearVelocity += (mForceAccumulator * (1.0f / mMass)) * static_cast<float>(dt);

        math::Vec3 angularAccel = mInertiaTensor.inverse() * mTorqueAccumulator;
        mAngularVelocity += angularAccel * static_cast<float>(dt);

        if (mTransform != nullptr) {
            math::Vec3 pos = mTransform->getPosition() + mLinearVelocity * static_cast<float>(dt);
            mTransform->setPosition(pos);

            float angle = mAngularVelocity.length() * static_cast<float>(dt);
            math::Vec3 axis = (angle > 0) ? mAngularVelocity / angle : math::Vec3(0, 0, 1);
            math::Quat deltaRotation = math::Quat::fromAxisAngle(axis, angle);

            math::Quat rotation = mTransform->getRotation();
            rotation = deltaRotation * rotation;
            mTransform->setRotation(rotation.normalized());
        }

        mForceAccumulator = math::Vec3::zero;
        mTorqueAccumulator = math::Vec3::zero;
    }

    void PhysicsBody::applyTorque(const math::Vec3& torque) {
        mTorqueAccumulator += torque;
    }
}
