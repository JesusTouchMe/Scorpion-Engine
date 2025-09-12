// Copyright 2025 JesusTouchMe

#include "scorpion/core/actor.h"

namespace scorpion {
    Actor::~Actor() {
        for (auto& [key, component] : mComponents) {
            component->onDestroy();
        }
        mComponents.clear();
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

    void Actor::render() {
        for (auto& [key, component] : mComponents) {
            if (component->isActive()) {
                if (auto* renderable = dynamic_cast<RenderableComponent*>(component.get())) {
                    renderable->onRender();
                }
            }
        }
    }
}
