// Copyright 2025 JesusTouchMe

#ifndef SCORPION_CAMERA_H
#define SCORPION_CAMERA_H 1

#include "scorpion/core/component.h"

#include "scorpion/util/math.h"

namespace scorpion::components {
    class SCORPION_API Camera : public Component {
    public:
        enum class Projection {
            Perspective = 0,
            Orthographic,
        };

        Camera(Actor* owner, math::Vec3 position, math::Vec3 target, math::Vec3 up, float fov_y, Projection projection)
            : Component(owner)
            , position(position)
            , target(target)
            , up(up)
            , fovY(fov_y)
            , projection(projection) {}

        math::Vec3 position;
        math::Vec3 target;
        math::Vec3 up;
        float fovY;
        Projection projection;

        void syncWithTransform();

        math::Vec3 forward() const;
        math::Vec3 right() const;
    };
}

#endif // SCORPION_CAMERA_H
