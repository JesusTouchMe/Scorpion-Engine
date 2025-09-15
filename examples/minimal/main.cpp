// Copyright 2025 JesusTouchMe

#include <scorpion/core/scorpion.h>

#include <scorpion/engine_std/transform.h>

#include <scorpion/render/input.h>
#include <scorpion/render/renderer.h>

#include <scorpion/util/actor_factory.h>

const char* vsSun = R"(
#version 330

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

uniform mat4 mvp;
uniform mat4 model;

out vec3 FragPos;
out vec3 Normal;

void main() {
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal  = mat3(model) * aNormal;
    gl_Position = mvp * vec4(aPos, 1.0);
}
)";

const char* fsSun = R"(
#version 330
in vec3 FragPos;
in vec3 Normal;
out vec4 FragColor;

uniform vec3 lightDir;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main() {
    vec3 norm = normalize(Normal);
    vec3 dir  = normalize(lightDir);

    float diff = max(dot(norm, dir), 0.0);
    vec3 diffuse = diff * lightColor;
    vec3 result = diffuse * objectColor;

    FragColor = vec4(result, 1.0);
}
)";

using namespace scorpion;

class OrbitalCamera : public Component {
public:
    using Component::Component;

    float sensitivity = 0.003;

    void onStart() override {
        mCamera = getOwner()->getComponent<components::Camera>();
        mTransform = getOwner()->getComponent<components::Transform>();
    }

    void onUpdate(double dt) override {
        if (mCamera == nullptr || mTransform == nullptr) return;

        if (input::IsMouseButtonDown(input::MouseButton::Left)) {
            math::Vec2 mouseDelta = input::GetMousePositionDelta();

            computeYaw(-mouseDelta.x * sensitivity);
            computePitch(-mouseDelta.y * sensitivity);
        }
    }

private:
    components::Camera* mCamera;
    components::Transform* mTransform;

    void computeYaw(float angle) {
        math::Vec3 up = mCamera->up.normalized();
        math::Vec3 targetPos = mCamera->target - mCamera->position;

        targetPos = targetPos.rotateByAxisAngle(up, angle);

        mCamera->position = mTransform->position = mCamera->target - targetPos;
    }

    void computePitch(float angle) {
        math::Vec3 up = mCamera->up.normalized();
        math::Vec3 targetPos = mCamera->target - mCamera->position;

        float maxAngleUp = up.angle(targetPos);
        maxAngleUp -= 0.001f;
        if (angle > maxAngleUp) angle = maxAngleUp;

        float maxAngleDown = (-up).angle(targetPos);
        maxAngleDown *= -1.0f;
        maxAngleDown += 0.001f;
        if (angle < maxAngleDown) angle = maxAngleDown;

        math::Vec3 right = mCamera->right();

        targetPos = targetPos.rotateByAxisAngle(right, angle);

        mCamera->position = mTransform->position = mCamera->target - targetPos;
        //mCamera->up = mCamera->up.rotateByAxisAngle(right, angle);
    }
};

int main() {
    render::InitWindow(1280, 720, "Scorpion Engine Examples - Minimal");

    Scene* scene = CreateScene(0);
    SetActiveScene(0);

    Actor* camera = actors::CreateCamera();
    camera->addComponent<OrbitalCamera>();
    scene->setActiveCamera(camera->getComponent<components::Camera>());

    SharedPtr<render::Shader> shader = render::CompileShader(vsSun, fsSun);

    math::Vec3 lightDir = math::Vec3(10, 15, 15).normalized();
    math::Vec3 lightColor = math::Vec3(1, 1, 0.9);

    shader->setUniformVec3("lightDir", lightDir);
    shader->setUniformVec3("lightColor", lightColor);

    Actor* ground = actors::CreateCube(math::Vec3::zero, {10, 0.1, 10}, math::Quat::identity, math::Color::green);
    Actor* cube = actors::CreateCube({0, 1, 0}, math::Vec3::one * 2, math::Quat::identity, math::Color::red);

    ground->applyShader(shader);
    cube->applyShader(shader);

    Run();

    return 0;
}
