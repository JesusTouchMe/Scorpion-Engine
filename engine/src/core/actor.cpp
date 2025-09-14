// Copyright 2025 JesusTouchMe

#include "scorpion/core/actor.h"

#include "scorpion/engine_std/transform.h"

namespace scorpion {
    Actor::Actor(Scene* scene)
        : mScene(scene) {}

    Actor::~Actor() {
        for (auto& [key, component] : mComponents) {
            component->onDestroy();
        }
    }

    void Actor::applyShader(const SharedPtr<render::Shader>& shader) {
        for (auto& [key, component] : mComponents) {
            //NOTE: this applies to inactive renderables too
            if (auto* renderable = dynamic_cast<RenderableComponent*>(component.get())) {
                renderable->setShader(shader);
            }
        }
    }

    void Actor::update(double dt) {
        onUpdate(dt);

        for (auto& [key, component] : mComponents) {
            if (!component->isActive()) continue;

            if (!component->mStarted) {
                component->onStart();
                component->mStarted = true;
            }

            component->onUpdate(dt);
        }
    }

    void Actor::renderPass(RenderableComponent::Layer pass) {
        for (auto& [key, component] : mComponents) {
            if (component->isActive()) {
                if (auto* renderable = dynamic_cast<RenderableComponent*>(component.get())) {
                    if (renderable->getLayer() == pass) {
                        renderable->beginShader();
                        renderable->onRender();
                        renderable->endShader();
                    }
                }
            }
        }
    }
}
