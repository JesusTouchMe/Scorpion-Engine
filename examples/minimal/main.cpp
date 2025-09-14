// Copyright 2025 JesusTouchMe

#include <scorpion/core/scorpion.h>

#include <scorpion/render/renderer.h>

#include <scorpion/util/actor_factory.h>

const char* vsSun = R"(
//TODO: vertex code for sun
)";

const char* fsSun = R"(
//TODO: fragment code for sun
)";

using namespace scorpion;

int main() {
    render::InitWindow(1280, 720, "Scorpion Engine Examples - Minimal");

    Scene* scene = CreateScene(0);
    SetActiveScene(0);

    Actor* camera = actors::CreateCamera();
    scene->setActiveCamera(camera->getComponent<components::Camera>());

    SharedPtr<render::Shader> shader = render::CompileShader(vsSun, fsSun);

    Actor* ground = actors::CreateCube(math::Vec3::zero, {10, 0.1, 10}, math::Quat::identity, math::Color::green);
    Actor* cube = actors::CreateCube({0, 1, 0}, math::Vec3::one * 2, math::Quat::identity, math::Color::red);

    ground->applyShader(shader);
    cube->applyShader(shader);

    Run();

    return 0;
}
