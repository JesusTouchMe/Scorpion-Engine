// Copyright 2025 JesusTouchMe

#include "scorpion/core/scene.h"

#include "scorpion/render/renderer.h"

namespace scorpion {
    void Scene::update(double dt) {
        for (auto& actor: mActors) {
            if (!actor->isActive()) continue;

            if (!actor->mStarted) {
                actor->onStart();
                actor->mStarted = true;
            }

            actor->update(dt);
        }
    }

    void Scene::render() {
        render::BeginDrawing();
        render::ClearWindow();

        if (mActiveCamera != nullptr) {
            mActiveCamera->syncWithTransform();

            render::Begin3D(mActiveCamera->position, mActiveCamera->target, mActiveCamera->up, mActiveCamera->fovY, static_cast<int>(mActiveCamera->projection));
            for (auto& actor: mActors) {
                if (actor->isActive()) actor->renderPass(RenderableComponent::Layer::World3D);
            }
            render::End3D();
        }

        for (auto& actor : mActors) {
            if (actor->isActive()) actor->renderPass(RenderableComponent::Layer::World2D);
        }

        for (auto& actor : mActors) {
            if (actor->isActive()) actor->renderPass(RenderableComponent::Layer::UI);
        }

        render::EndDrawing();
    }

    bool Scene::removeActor(Actor* actor) {
        for (size_t i = 0; i < mActors.size(); i++) {
            if (mActors[i].get() == actor) {
                mActors[i]->onDestroy();
                mActors[i] = std::move(mActors.back());
                mActors.pop_back();
                return true;
            }
        }

        return false;
    }

    void Scene::reset() {
        for (auto& actor : mActors) {
            actor->onDestroy();
            actor->mStarted = false;
        }
    }
}
