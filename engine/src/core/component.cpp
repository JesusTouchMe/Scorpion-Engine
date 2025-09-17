// Copyright 2025 JesusTouchMe

#include "scorpion/core/component.h"

namespace scorpion {
    void RenderableComponent::beginShader() {
        if (mShader != nullptr) {
            mShader->begin();
            beginShader0();
        }
    }

    void RenderableComponent::endShader() {
        if (mShader != nullptr) {
            endShader0();
            mShader->end();
        }
    }
}
