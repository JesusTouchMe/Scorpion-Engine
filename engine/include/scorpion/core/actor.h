// Copyright 2025 JesusTouchMe

#ifndef SCORPION_ACTOR_H
#define SCORPION_ACTOR_H 1

#include "scorpion/core/component.h"

#include "scorpion/util/std_types.h"

#include <typeindex>

namespace scorpion {
    class Scene;

    class Actor {
    friend class Scene;
    public:
        explicit Actor(Scene* scene) : mScene(scene) {}
        virtual ~Actor();

        virtual void onStart() {}
        virtual void onUpdate(double dt) {}
        virtual void onDestroy() {}

        template<class T, typename... Args>
        T* addComponent(Args&&... args) {
            std::type_index type = typeid(T);
            if (mComponents.contains(type)) {
                return static_cast<T*>(mComponents[type].get());
            }

            UniquePtr<T> component = MakeUnique<T>(this, std::forward<Args>(args)...);
            T* ptr = component.get();

            mComponents[type] = std::move(component);

            return ptr;
        }

        template<class T>
        T* getComponent() {
            auto it = mComponents.find(typeid(T));
            if (it != mComponents.end()) return static_cast<T*>(it->second.get());
            else return nullptr;
        }

        template<class T>
        bool removeComponent() {
            auto it = mComponents.find(typeid(T));
            if (it != mComponents.end()) {
                it->second->onDestroy();
                mComponents.erase(it);
                return true;
            }

            return false;
        }

        Scene* getScene() const { return mScene; }

        bool isActive() const { return mActive; }
        void setActive(bool active) { mActive = active; }

    private:
        Scene* mScene;
        bool mActive = true;
        bool mStarted = false;

        HashMap<std::type_index, UniquePtr<Component>> mComponents;

        void update(double dt);
        void render();
    };
}

#endif //SCORPION_ACTOR_H