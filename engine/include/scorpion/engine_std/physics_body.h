// Copyright 2025 JesusTouchMe

#ifndef SCORPION_PHYSICS_BODY_H
#define SCORPION_PHYSICS_BODY_H 1

#include "scorpion/core/component.h"

#include "scorpion/engine_std/transform.h"

#include "scorpion/util/math.h"

namespace scorpion::components {
    class SCORPION_API PhysicsBody : public Component {
    public:
        static const math::Vec3 gravity;

        PhysicsBody(Actor* owner, float mass, bool gravity = true, bool kinematic = false);

        void onStart() override;
        void onUpdate(double dt) override;

        void applyTorque(const math::Vec3& torque);

    private:
        Transform* mTransform;

        float mMass;
        bool mGravity;
        bool mKinematic;

        math::Vec3 mLinearVelocity;
        math::Vec3 mAngularVelocity;
        math::Matrix3 mInertiaTensor;

        math::Vec3 mForceAccumulator;
        math::Vec3 mTorqueAccumulator;
    };
}

#endif // SCORPION_PHYSICS_BODY_H
