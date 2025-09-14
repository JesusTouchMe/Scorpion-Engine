// Copyright 2025 JesusTouchMe

#ifndef SCORPION_ACTOR_FACTORY_H
#define SCORPION_ACTOR_FACTORY_H 1

#include "scorpion/core/scene.h"

#include "scorpion/util/math.h"

namespace scorpion::actors {
    SCORPION_API Actor* CreateCamera(math::Vec3 position = math::Vec3(10, 10, 10), math::Vec3 target = math::Vec3::zero, math::Vec3 up = math::Vec3(0, 1, 0), float fovY = 45, components::Camera::Projection projection = components::Camera::Projection::Perspective, Scene* scene = nullptr);

    SCORPION_API Actor* CreateActorWithTransform(math::Vec3 position = math::Vec3::zero, math::Vec3 size = math::Vec3::zero, math::Quat rotation = math::Quat::identity, Scene* scene = nullptr);
    SCORPION_API Actor* CreateCube(math::Vec3 position, math::Vec3 size, math::Quat rotation, math::Color color, Scene* scene = nullptr);
}

#endif // SCORPION_ACTOR_FACTORY_H
