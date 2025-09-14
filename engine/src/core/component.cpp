// Copyright 2025 JesusTouchMe

#include "scorpion/core/component.h"

namespace scorpion {
    void RenderableComponent::beginShader() {
        if (mShader != nullptr) {
            beginShader0();
            mShader->begin();
        }
    }

    void RenderableComponent::endShader() {
        if (mShader != nullptr) {
            endShader0();
            mShader->end();
        }
    }
}
