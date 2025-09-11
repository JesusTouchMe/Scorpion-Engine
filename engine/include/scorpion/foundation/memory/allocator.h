// Copyright 2025 JesusTouchMe

#ifndef SCORPION_ALLOCATOR_H
#define SCORPION_ALLOCATOR_H 1

#include "scorpion/core/api.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ScorpionArena ScorpionArena;

SCORPION_API ScorpionArena* ScorpionCreateArena(size_t minimumChunkSize, size_t firstChunkSize);

SCORPION_API void ScorpionDestroyArena(ScorpionArena* arena);

SCORPION_API void ScorpionArenaReset(ScorpionArena* arena);

SCORPION_API void* ScorpionArenaAlloc(ScorpionArena* arena, size_t size);

SCORPION_API void* ScorpionHeapAlloc(size_t size);

SCORPION_API void* ScorpionHeapRealloc(void* ptr, size_t size);

SCORPION_API void ScorpionHeapFree(void* ptr);

#ifdef __cplusplus
}

namespace scorpion::memory {
    class Arena {
    public:
        Arena(size_t minimumChunkSize, size_t firstChunkSize)
            : mArena(ScorpionCreateArena(minimumChunkSize, firstChunkSize)) {}

        ~Arena() {
            ScorpionDestroyArena(mArena);
        }

        void reset() {
            ScorpionResetArena(mArena);
        }

        void* allocate(size_t size) {
            return ScorpionArenaAlloc(mArena, size);
        }

    private:
        ScorpionArena* mArena;
    };

    // Used for stl containers and shit
    template<typename T>
    struct StdHeapAllocator {
        using value_type = T;

        StdHeapAllocator() = default;

        template<typename U>
        constexpr StdHeapAllocator(const StdHeapAllocator<U>&) noexcept {}

        T* allocate(size_t n) {
            return static_cast<T*>(ScorpionHeapAlloc(n * sizeof(T)));
        }

        void deallocate(void* p, size_t n) noexcept {
            ScorpionHeapFree(p);
        }
    };
}
#endif

#endif // SCORPION_ALLOCATOR_H
