// Copyright 2025 JesusTouchMe

#include <scorpion/core/scorpion.h>

#include <scorpion/render/renderer.h>

int main() {
    scorpion::render::InitWindow(1280, 720, "Scorpion Engine Examples - Minimal");

    scorpion::Run();

    return 0;
}