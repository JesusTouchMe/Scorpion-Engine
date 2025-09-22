// Copyright 2025 JesusTouchMe

#ifndef SCORPION_CAMERA_H
#define SCORPION_CAMERA_H 1

#include "scorpion/core/component.h"

#include "scorpion/engine_std/transform.h"

#include "scorpion/util/math.h"

namespace scorpion::components {
    class SCORPION_API Camera : public Component {
    public:
        enum class Projection {
            Perspective = 0,
            Orthographic,
        };

        Camera(Actor* owner, math::Vec3 position, math::Vec3 target, math::Vec3 up, float fovY, Projection projection);

        void onStart() override;
        void onUpdate(double dt) override;

        math::Vec3 getPosition() const;
        math::Vec3 getTarget() const;
        math::Vec3 getUp() const;
        math::Vec3 getForward() const;
        math::Vec3 getRight() const;
        float getFovY() const;
        Projection getProjection() const;

        void setPosition(math::Vec3 position);
        void setTarget(math::Vec3 target);
        void setUp(math::Vec3 up);
        void setFovY(float fovY);
        void setProjection(Projection projection);

    private:
        Transform* mTransform;

        math::Vec3 mPosition;
        math::Vec3 mTarget;
        math::Vec3 mUp;
        float mFovY;
        Projection mProjection;
    };
}

#endif // SCORPION_CAMERA_H
