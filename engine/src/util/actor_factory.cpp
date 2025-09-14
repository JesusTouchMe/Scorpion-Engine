// Copyright 2025 JesusTouchMe

#include "scorpion/core/scorpion.h"

#include "scorpion/engine_std/transform.h"
#include "scorpion/engine_std/cube_renderer.h"

#include "scorpion/util/actor_factory.h"

#define CHECK_SCENE(scene) if (scene == nullptr) { scene = GetActiveScene(); if (scene == nullptr) return nullptr; }

namespace scorpion::actors {
    using namespace components;

    Actor* CreateCamera(math::Vec3 position, math::Vec3 target, math::Vec3 up, float fovY, Camera::Projection projection, Scene* scene) {
        CHECK_SCENE(scene);

        math::Vec3 forward = (target - position).normalized();
        math::Vec3 right = forward.cross(up).normalized();
        math::Vec3 cross_up = right.cross(forward);

        math::Matrix4 rotMat;
        rotMat.m[0] = right.x;
        rotMat.m[1] = right.y;
        rotMat.m[2] = right.z;
        rotMat.m[3] = 0.0f;
        rotMat.m[4] = cross_up.x;
        rotMat.m[5] = cross_up.y;
        rotMat.m[6] = cross_up.z;
        rotMat.m[7] = 0.0f;
        rotMat.m[8] = -forward.x;
        rotMat.m[9] = -forward.y;
        rotMat.m[10] = -forward.z;
        rotMat.m[11] = 0.0f;
        rotMat.m[12] = 0.0f;
        rotMat.m[13] = 0.0f;
        rotMat.m[14] = 0.0f;
        rotMat.m[15] = 1.0f;

        math::Quat rotation = math::Quat::fromMatrix(rotMat);

        Actor* actor = CreateActorWithTransform(position, math::Vec3(1, 1, 1), rotation, scene);
        actor->addComponent<Camera>(position, target, up, fovY, projection);

        return actor;
    }

    Actor* CreateActorWithTransform(math::Vec3 position, math::Vec3 size, math::Quat rotation, Scene* scene) {
        CHECK_SCENE(scene);

        Actor* actor = scene->addActor<Actor>();
        actor->addComponent<Transform>(position, size, rotation);

        return actor;
    }

    Actor* CreateCube(math::Vec3 position, math::Vec3 size, math::Quat rotation, math::Color color, Scene* scene) {
        CHECK_SCENE(scene);

        Actor* actor = CreateActorWithTransform(position, size, rotation, scene);
        actor->addComponent<CubeRenderer>(color);

        return actor;
    }
}
