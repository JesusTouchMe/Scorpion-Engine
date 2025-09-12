// Copyright 2025 JesusTouchMe

#ifndef SCORPION_COMPONENT_H
#define SCORPION_COMPONENT_H 1

namespace scorpion {
    class Actor;

    class Component {
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

    class RenderableComponent : public Component {
    public:
        using Component::Component;

        virtual void onRender() = 0;
    };
}

#endif //SCORPION_COMPONENT_H