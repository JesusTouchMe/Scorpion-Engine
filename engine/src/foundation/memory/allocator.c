// Copyright 2025 JesusTouchMe

#include "scorpion/foundation/memory/allocator.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct ArenaChunk {
    size_t size;
    size_t used;
    struct ArenaChunk* next;
    char data[];
} ArenaChunk;

struct ScorpionArena {
    ArenaChunk* head;
    ArenaChunk* current;
    size_t minimumChunkSize;
};

ScorpionArena* ScorpionCreateArena(size_t minimumChunkSize, size_t firstChunkSize) {
    if (firstChunkSize < minimumChunkSize) firstChunkSize = minimumChunkSize;

    size_t offset = (sizeof(ScorpionArena) + 15) & ~((size_t)15);
    size_t totalSize = offset + firstChunkSize;

    char* memory = ScorpionHeapAlloc(totalSize);

    ScorpionArena* arena = (ScorpionArena*)memory;

    ArenaChunk* firstChunk = (ArenaChunk*)(memory + offset);
    firstChunk->size = firstChunkSize;
    firstChunk->used = 0;
    firstChunk->next = NULL;

    arena->head = firstChunk;
    arena->minimumChunkSize = minimumChunkSize;

    return arena;
}

void ScorpionDestroyArena(ScorpionArena* arena) {
    size_t offset = (sizeof(ScorpionArena) + 15) & ~((size_t)15);
    char* arenaChunk = (char*) arena + offset;

    for (ArenaChunk* current = arena->head; current != NULL; current = current->next) {
        ArenaChunk* next = current->next;

        if ((char*) current != arenaChunk) {
            ScorpionHeapFree(arenaChunk);
        }
    }

    ScorpionHeapFree(arena);
}

void ScorpionArenaReset(ScorpionArena* arena) {
    for (ArenaChunk* current = arena->head; current != NULL; current = current->next) {
        current->used = 0;
    }
    arena->current = arena->head;
}

void* ScorpionArenaAlloc(ScorpionArena* arena, size_t size) {
    size = (size + 7) & ~7;

    if (arena->current->used + size > arena->current->size) {
        size_t newChunkSize = arena->minimumChunkSize;
        if (newChunkSize < size) newChunkSize += size;

        ArenaChunk* newChunk = ScorpionHeapAlloc(sizeof(ArenaChunk) + newChunkSize);

        newChunk->size = newChunkSize;
        newChunk->used = 0;
        newChunk->next = NULL;

        arena->current->next = newChunk;
        arena->current = newChunk;
    }

    void* ptr = arena->current->data + arena->current->used;
    arena->current->used += size;
    return ptr;
}

void* ScorpionHeapAlloc(size_t size) {
    void* ptr = malloc(size);
    if (ptr == NULL) {
        //TODO: NICE ERROR SYSTEM RAHHH
        printf("Failed to allocate %zu bytes\n", size);
        exit(1);
    }
    return ptr;
}

void* ScorpionHeapRealloc(void* ptr, size_t size) {
    return realloc(ptr, size);
}

void ScorpionHeapFree(void* ptr) {
    free(ptr);
}
