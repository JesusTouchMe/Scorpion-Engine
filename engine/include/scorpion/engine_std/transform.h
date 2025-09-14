// Copyright 2025 JesusTouchMe

#ifndef SCORPION_STD_TRANSFORM_H
#define SCORPION_STD_TRANSFORM_H 1

#include "scorpion/core/component.h"

#include "scorpion/util/math.h"

namespace scorpion::components {
    class SCORPION_API Transform : public Component {
    public:
        Transform(Actor* owner, math::Vec3 position, math::Vec3 scale, math::Quat rotation)
            : Component(owner)
            , position(position)
            , size(scale)
            , rotation(rotation) {}

        math::Vec3 position;
        math::Vec3 size;
        math::Quat rotation;

        math::Matrix4 getMatrix() const;
    };
}

#endif //SCORPION_STD_TRANSFORM_H