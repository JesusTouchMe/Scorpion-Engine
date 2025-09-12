// Copyright 2025 JesusTouchMe

#ifndef SCENE_H
#define SCENE_H 1

#include "scorpion/core/actor.h"

namespace scorpion {
    class Scene {
    public:
        void update(double dt);
        void render();

        template<class T, typename... Args>
        T* addActor(Args&&... args) {
            UniquePtr<T> actor = MakeUnique<T>(this, std::forward<Args>(args)...);
            T* ptr = actor.get();

            mActors.push_back(std::move(actor));

            return ptr;
        }

        bool removeActor(Actor* actor);

        void reset();

    private:
        Vector<UniquePtr<Actor>> mActors;
    };
}

#endif //SCENE_H