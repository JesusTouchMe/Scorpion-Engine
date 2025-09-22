// Copyright 2025 JesusTouchMe

#ifndef SCORPION_STD_TRANSFORM_H
#define SCORPION_STD_TRANSFORM_H 1

#include "scorpion/core/component.h"

#include "scorpion/util/math.h"

namespace scorpion::components {
    class SCORPION_API Transform : public Component {
    public:
        Transform(Actor* owner, math::Vec3 position, math::Vec3 size, math::Quat rotation);

        math::Matrix4 getMatrix() const;

        math::Vec3 getPosition() const;
        math::Vec3 getSize() const;
        math::Quat getRotation() const;

        void setPosition(math::Vec3 position);
        void setSize(math::Vec3 size);
        void setRotation(math::Quat rotation);

    private:
        math::Vec3 mPosition;
        math::Vec3 mSize;
        math::Quat mRotation;
    };
}

#endif //SCORPION_STD_TRANSFORM_H