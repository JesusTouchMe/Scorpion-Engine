// Copyright 2025 JesusTouchMe

// Provides typedefs for std classes using Scorpions heap allocator

#ifndef STD_TYPES_H
#define STD_TYPES_H 1

#include "scorpion/foundation/memory/allocator.h"

#include <memory>
#include <unordered_map>
#include <vector>

namespace scorpion {
    template<class T>
    using SharedPtr = std::shared_ptr<T>;

    template<class T, class... Args>
    SharedPtr<T> MakeShared(Args&&... args) {
        memory::StdHeapAllocator<T> alloc;
        return std::allocate_shared<T>(alloc, std::forward<Args>(args)...);
    }

    template<class T>
    using UniquePtr = std::unique_ptr<T, memory::StdHeapDeleter<T>>;

    template<class T, class... Args>
    UniquePtr<T> MakeUnique(Args&&... args) {
        memory::StdHeapAllocator<T> alloc;
        T* memory = alloc.allocate(1);
        new(memory) T(std::forward<Args>(args)...);
        return UniquePtr<T>(memory);
    }

    template<class T>
    using WeakPtr = std::weak_ptr<T>;

    template<class K, class V, typename Hash = std::hash<K>, typename Eq = std::equal_to<K>>
    using HashMap = std::unordered_map<K, V, Hash, Eq, memory::StdHeapAllocator<std::pair<const K, V>>>;

    using String = std::basic_string<char, std::char_traits<char>, memory::StdHeapAllocator<char>>;

    template<class T>
    using Vector = std::vector<T, memory::StdHeapAllocator<T>>;
}

#endif //STD_TYPES_H