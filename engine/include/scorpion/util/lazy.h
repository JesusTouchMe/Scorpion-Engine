// Copyright 2025 JesusTouchMe

#ifndef SCORPION_LAZY_H
#define SCORPION_LAZY_H 1

#include <functional>
#include <optional>

namespace scorpion {
    template<class T>
    class SCORPION_API LazyVar {
    public:
        explicit LazyVar(std::function<T()> init) : mInit(std::move(init)) {}

        const T& get() const {
            if (!mValue) {
                mValue.emplace(mInit());
            }

            return mValue.value();
        }

        operator const T&() const {
            return get();
        }

    private:
        std::function<T()> mInit;
        mutable std::optional<T> mValue;
    };
}

#endif // SCORPION_LAZY_H
