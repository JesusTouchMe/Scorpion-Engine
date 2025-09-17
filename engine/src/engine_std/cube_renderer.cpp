// Copyright 2025 JesusTouchMe

#include "scorpion/core/scorpion.h"

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
        Camera* camera = GetActiveScene()->getActiveCamera();
        Transform* transform = getOwner()->getComponent<Transform>();
        if (transform == nullptr) return;

        math::Matrix4 model = transform->getMatrix();
        math::Matrix4 view = math::Matrix4::lookAt(camera->position, camera->target, camera->up);
        math::Matrix4 projection = math::Matrix4::perspective(camera->fovY, static_cast<float>(render::GetWindowWidth()) / static_cast<float>(render::GetWindowHeight()), 0.1f, 100.0f);
        math::Matrix4 mvp = projection * view * model;

        shader()->setUniformMatrix4("mvp", mvp);
        shader()->setUniformMatrix4("model", model);
        shader()->setUniformVec3("objectColor", mColor.toVec3());
    }
}
