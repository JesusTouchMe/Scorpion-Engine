// Copyright 2025 JesusTouchMe

#include "scorpion/core/actor.h"

#include "scorpion/engine_std/cube_renderer.h"
#include "scorpion/engine_std/transform.h"

#include "scorpion/render/renderer.h"

namespace scorpion::components {
    CubeRenderer::CubeRenderer(Actor* actor, math::Color color)
        : RenderableComponent(actor, Layer::World3D)
        , mColor(color) {}

    void CubeRenderer::onRender() {
        Transform* transform = getOwner()->getComponent<Transform>();
        if (transform == nullptr) return;

        render::DrawCube(transform->position, transform->size, transform->rotation, mColor);
    }

    void CubeRenderer::beginShader0() {
        math::Vec3 lightDir = math::Vec3(10, 10, 10).normalized();
        math::Vec3 lightColor = math::Vec3(1, 1, 0.9f);

        shader()->setUniformVec3("lightDir", lightDir);
        shader()->setUniformVec3("lightColor", lightColor);
        shader()->setUniformVec3("baseColor", mColor.toVec3());
        shader()->setUniformFloat("ambientStrength", 0.2);
    }
}
