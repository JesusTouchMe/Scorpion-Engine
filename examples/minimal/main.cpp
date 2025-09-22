// Copyright 2025 JesusTouchMe

#include <scorpion/core/scorpion.h>

#include <scorpion/engine_std/physics_body.h>
#include <scorpion/engine_std/transform.h>

#include <scorpion/hal/input.h>
#include <scorpion/hal/renderer.h>

#include <scorpion/util/actor_factory.h>


const char* vsSun = R"(
#version 330

in vec3 vertexPosition;
in vec3 vertexNormal;
in vec4 vertexColor;

uniform mat4 mvp;
uniform mat4 model;

out vec3 fragPos;
out vec3 fragNormal;
out vec4 fragColorAttrib;

void main() {
    fragPos = vec3(model * vec4(vertexPosition, 1.0));
    fragNormal = mat3(transpose(inverse(model))) * vertexNormal;
    fragColorAttrib = vertexColor;
    gl_Position = mvp * vec4(vertexPosition, 1.0);
}
)";

const char* fsSun = R"(
#version 330

in vec3 fragPos;
in vec3 fragNormal;
in vec4 fragColorAttrib;

uniform vec3 lightDir;       // normalized
uniform vec3 lightColor;
uniform vec3 ambientColor;

uniform vec3 cameraPos;      // world-space eye
uniform float shininess;     // higher = smaller highlight
uniform float specStrength;  // how intense specular is

out vec4 fragColor;

void main() {
    vec3 N = normalize(fragNormal);
    vec3 L = normalize(-lightDir);  // light shining *onto* surface

    // --- Diffuse ---
    float diff = max(dot(N, L), 0.0);
    vec3 diffuse = lightColor * diff;

    // --- Specular (Blinn-Phong) ---
    vec3 V = normalize(cameraPos - fragPos); // view vector
    vec3 H = normalize(L + V);               // half vector
    float spec = pow(max(dot(N, H), 0.0), shininess);
    vec3 specular = lightColor * specStrength * spec;

    // --- Final ---
    vec3 lighting = ambientColor + diffuse + specular;
    vec3 baseColor = fragColorAttrib.rgb;
    fragColor = vec4(baseColor * lighting, fragColorAttrib.a);
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

        zoom(-input::GetMouseWheel());
    }

private:
    components::Camera* mCamera;
    components::Transform* mTransform;

    void computeYaw(float angle) {
        math::Vec3 up = mCamera->getUp().normalized();
        math::Vec3 targetPos = mCamera->getForward();

        targetPos = targetPos.rotateByAxisAngle(up, angle);

        math::Vec3 pos = mCamera->getTarget() - targetPos;
        mCamera->setPosition(pos);
        mTransform->setPosition(pos);
    }

    void computePitch(float angle) {
        math::Vec3 up = mCamera->getUp().normalized();
        math::Vec3 targetPos = mCamera->getForward();

        float maxAngleUp = up.angle(targetPos);
        maxAngleUp -= 0.001f;
        if (angle > maxAngleUp) angle = maxAngleUp;

        float maxAngleDown = (-up).angle(targetPos);
        maxAngleDown *= -1.0f;
        maxAngleDown += 0.001f;
        if (angle < maxAngleDown) angle = maxAngleDown;

        math::Vec3 right = mCamera->getRight().normalized();

        targetPos = targetPos.rotateByAxisAngle(right, angle);

        math::Vec3 pos = mCamera->getTarget() - targetPos;
        mCamera->setPosition(pos);
        mTransform->setPosition(pos);
    }

    void zoom(float delta) {
        float distance = mCamera->getPosition().distanceTo(mCamera->getTarget()) + delta;
        if (distance <= 0) distance = 0.001f;

        math::Vec3 forward = mCamera->getForward().normalized();

        math::Vec3 pos = mCamera->getTarget() + forward * -distance;
        mCamera->setPosition(pos);
        mTransform->setPosition(pos);
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

    math::Vec3 lightDir = math::Vec3(-0.2f, -0.4f, -0.3f);
    math::Vec3 lightColor = math::Vec3(1, 1, 1);
    math::Vec3 ambientColor = math::Vec3(0.175f, 0.175f, 0.175f);

    shader->setUniformVec3("lightDir", lightDir);
    shader->setUniformVec3("lightColor", lightColor);
    shader->setUniformVec3("ambientColor", ambientColor);
    shader->setUniformFloat("shininess", 32);
    shader->setUniformFloat("specStrength", 0.5f);

    Actor* ground = actors::CreateCube(math::Vec3::zero, {10, 0.01, 10}, math::Quat::identity, math::Color::green);
    Actor* cube = actors::CreateCube({0, 4, 0}, math::Vec3::one * 2, math::Quat::identity, math::Color::red);

    cube->addComponent<components::PhysicsBody>(1);

    cube->getComponent<components::PhysicsBody>()->applyTorque({0, 0.005, 0});

    ground->applyShader(shader);
    cube->applyShader(shader);

    math::Vec3 origin = math::Vec3::zero;
    math::Vec3 dir = lightDir.normalized();
    float length = 100;
    float thickness = 0.1f;

    math::Vec3 end = origin + dir;
    math::Vec3 mid = origin.lerp(end, 0.5f);

    math::Vec3 defaultDir = {0, 1, 0};
    math::Quat rotation = math::Quat::fromTo(defaultDir, dir);

    math::Vec3 size = {thickness, thickness, length};

    actors::CreateCube(mid, size, rotation, math::Color::blue);

    AddUpdateHook([camera, shader](auto& hook) {
        shader->setUniformVec3("cameraPos", camera->getComponent<components::Transform>()->getPosition().normalized());
    });

    Run();

    return 0;
}
