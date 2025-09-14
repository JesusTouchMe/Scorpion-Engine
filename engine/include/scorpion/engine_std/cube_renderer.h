// Copyright 2025 JesusTouchMe

#ifndef SCORPION_CUBE_RENDERER_H
#define SCORPION_CUBE_RENDERER_H 1

#include "scorpion/core/component.h"

#include "scorpion/util/math.h"

namespace scorpion::components {
    class SCORPION_API CubeRenderer : public RenderableComponent {
    public:
        CubeRenderer(Actor* actor, math::Color color);

        void onRender() override;

    protected:
        void beginShader0() override;

    private:
        math::Color mColor;
    };
}

#endif // SCORPION_CUBE_RENDERER_H
