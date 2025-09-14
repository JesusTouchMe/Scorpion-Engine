// Copyright 2025 JesusTouchMe

#ifndef SCORPION_COMPONENT_H
#define SCORPION_COMPONENT_H 1

#include <utility>

#include "scorpion/core/api.h"

#include "scorpion/render/renderer.h"

namespace scorpion {
    class Actor;

    class SCORPION_API Component {
    friend class Actor;
    public:
        explicit Component(Actor* owner) : mOwner(owner) {}
        virtual ~Component() = default;

        virtual void onStart() {}
        virtual void onUpdate(double dt) {}
        virtual void onDestroy() {}

        Actor* getOwner() const { return mOwner; }

        bool isActive() const { return mActive; }
        void setActive(bool active) { mActive = active; }

    private:
        Actor* mOwner;
        bool mActive = true;
        bool mStarted = false;
    };

    class SCORPION_API RenderableComponent : public Component {
    public:
        enum class Layer {
            World2D,
            World3D,
            UI
        };

        RenderableComponent(Actor* owner, Layer layer) : Component(owner), mLayer(layer) {}

        virtual void onRender() = 0;

        void beginShader();
        void endShader();

        Layer getLayer() const { return mLayer; }

        SharedPtr<render::Shader> getShader() const { return mShader; }
        void setShader(SharedPtr<render::Shader> shader) { mShader = std::move(shader); }

    protected:
        virtual void beginShader0() {}
        virtual void endShader0() {}

        render::Shader* shader() const { return mShader.get(); }

    private:
        Layer mLayer;
        SharedPtr<render::Shader> mShader;
    };
}

#endif //SCORPION_COMPONENT_H