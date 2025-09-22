// Copyright 2025 JesusTouchMe

#include "scorpion/core/scorpion.h"

#include "scorpion/engine_std/cube_renderer.h"
#include "scorpion/engine_std/transform.h"

#include "scorpion/hal/renderer.h"

namespace scorpion::components {
    CubeRenderer::CubeRenderer(Actor* actor, math::Color color)
        : RenderableComponent(actor, Layer::World3D)
        , mColor(color) {}

    void CubeRenderer::onStart() {
        mTransform = getOwner()->getComponent<Transform>();
    }

    void CubeRenderer::onRender() {
        if (mTransform == nullptr) return;

        render::DrawCube(mTransform->getPosition(), mTransform->getSize(), mTransform->getRotation(), mColor);
    }

    math::Color CubeRenderer::getColor() const {
        return mColor;
    }

    void CubeRenderer::beginShader0() {
        Camera* camera = GetActiveScene()->getActiveCamera();
        Transform* transform = getOwner()->getComponent<Transform>();
        if (transform == nullptr) return;

        math::Matrix4 model = transform->getMatrix();
        math::Matrix4 view = math::Matrix4::lookAt(camera->getPosition(), camera->getTarget(), camera->getUp());
        math::Matrix4 projection = math::Matrix4::perspective(camera->getFovY(), static_cast<float>(render::GetWindowWidth()) / static_cast<float>(render::GetWindowHeight()), 0.1f, 100.0f);
        math::Matrix4 mvp = projection * view * model;

        shader()->setUniformMatrix4("mvp", mvp);
        shader()->setUniformMatrix4("model", model);
    }
}
