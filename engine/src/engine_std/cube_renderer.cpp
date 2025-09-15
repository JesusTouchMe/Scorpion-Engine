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
        math::Matrix4 model = math::Matrix4::identity();
        math::Matrix4 view = math::Matrix4::lookAt()

        shader()->setUniformVec3("objectColor", mColor.toVec3());
    }
}
