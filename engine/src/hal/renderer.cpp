// Copyright 2025 JesusTouchMe

#include "scorpion/engine_std/camera.h"

#include "scorpion/hal/renderer.h"

#include "scorpion/util/lazy.h"

#include <config.h>
#include <raylib.h>
#include <rlgl.h>

namespace scorpion::render {
    Shader::Shader(void* handle)
        : mHandle(handle) {
        unsigned int rlId = static_cast<unsigned int>(reinterpret_cast<uintptr_t>(mHandle));

        if (rlId == rlGetShaderIdDefault()) mInternalState = rlGetShaderLocsDefault();
        else if (rlId > 0) {
            auto locs = static_cast<int*>(ScorpionHeapAlloc(RL_MAX_SHADER_LOCATIONS * sizeof(int)));

            locs[SHADER_LOC_VERTEX_POSITION] = rlGetLocationAttrib(rlId, RL_DEFAULT_SHADER_ATTRIB_NAME_POSITION);
            locs[SHADER_LOC_VERTEX_TEXCOORD01] = rlGetLocationAttrib(rlId, RL_DEFAULT_SHADER_ATTRIB_NAME_TEXCOORD);
            locs[SHADER_LOC_VERTEX_TEXCOORD02] = rlGetLocationAttrib(rlId, RL_DEFAULT_SHADER_ATTRIB_NAME_TEXCOORD2);
            locs[SHADER_LOC_VERTEX_NORMAL] = rlGetLocationAttrib(rlId, RL_DEFAULT_SHADER_ATTRIB_NAME_NORMAL);
            locs[SHADER_LOC_VERTEX_TANGENT] = rlGetLocationAttrib(rlId, RL_DEFAULT_SHADER_ATTRIB_NAME_TANGENT);
            locs[SHADER_LOC_VERTEX_COLOR] = rlGetLocationAttrib(rlId, RL_DEFAULT_SHADER_ATTRIB_NAME_COLOR);
            locs[SHADER_LOC_VERTEX_BONEIDS] = rlGetLocationAttrib(rlId, "vertexBoneIds");
            locs[SHADER_LOC_VERTEX_BONEWEIGHTS] = rlGetLocationAttrib(rlId, "vertexBoneWeights");
            locs[SHADER_LOC_VERTEX_INSTANCE_TX] = rlGetLocationAttrib(rlId, "instanceTransform");

            locs[SHADER_LOC_MATRIX_MVP] = rlGetLocationUniform(rlId, RL_DEFAULT_SHADER_UNIFORM_NAME_MVP);
            locs[SHADER_LOC_MATRIX_VIEW] = rlGetLocationUniform(rlId, RL_DEFAULT_SHADER_UNIFORM_NAME_VIEW);
            locs[SHADER_LOC_MATRIX_PROJECTION] = rlGetLocationUniform(rlId, RL_DEFAULT_SHADER_UNIFORM_NAME_PROJECTION);
            locs[SHADER_LOC_MATRIX_MODEL] = rlGetLocationUniform(rlId, RL_DEFAULT_SHADER_UNIFORM_NAME_MODEL);
            locs[SHADER_LOC_MATRIX_NORMAL] = rlGetLocationUniform(rlId, RL_DEFAULT_SHADER_UNIFORM_NAME_NORMAL);
            locs[SHADER_LOC_BONE_MATRICES] = rlGetLocationUniform(rlId, "boneMatrices");

            locs[SHADER_LOC_COLOR_DIFFUSE] = rlGetLocationUniform(rlId, RL_DEFAULT_SHADER_UNIFORM_NAME_COLOR);
            locs[SHADER_LOC_MAP_DIFFUSE] = rlGetLocationUniform(rlId, RL_DEFAULT_SHADER_SAMPLER2D_NAME_TEXTURE0);
            locs[SHADER_LOC_MAP_SPECULAR] = rlGetLocationUniform(rlId, RL_DEFAULT_SHADER_SAMPLER2D_NAME_TEXTURE1);
            locs[SHADER_LOC_MAP_NORMAL] = rlGetLocationUniform(rlId, RL_DEFAULT_SHADER_SAMPLER2D_NAME_TEXTURE2);

            mInternalState = locs;
        }
    }

    Shader::~Shader() {
        if (mBegun) end();

        unsigned int rlId = static_cast<unsigned int>(reinterpret_cast<uintptr_t>(mHandle));
        if (rlId != rlGetShaderIdDefault()) {
            rlUnloadShaderProgram(rlId);
            ScorpionHeapFree(mInternalState);
        }
    }

    void Shader::begin() {
        unsigned int rlId = static_cast<unsigned int>(reinterpret_cast<uintptr_t>(mHandle));
        int* locs = static_cast<int*>(mInternalState);
        rlSetShader(rlId, locs);
    }

    void Shader::end() {
        rlSetShader(rlGetShaderIdDefault(), rlGetShaderLocsDefault());
    }

    int Shader::getUniformLocation(const String& name) {
        if (auto it = mUniformLocs.find(name); it != mUniformLocs.end()) return it->second;

        unsigned int rlId = static_cast<unsigned int>(reinterpret_cast<uintptr_t>(mHandle));
        int loc = rlGetLocationUniform(rlId, name.c_str());
        mUniformLocs[name] = loc;

        return loc;
    }

    int Shader::getAttribLocation(const String& name) {
        if (auto it = mAttribLocs.find(name); it != mAttribLocs.end()) return it->second;

        unsigned int rlId = static_cast<unsigned int>(reinterpret_cast<uintptr_t>(mHandle));
        int loc = rlGetLocationAttrib(rlId, name.c_str());
        mAttribLocs[name] = loc;

        return loc;
    }

    void Shader::setUniformFloat(const String& name, float value) {
        unsigned int rlId = static_cast<unsigned int>(reinterpret_cast<uintptr_t>(mHandle));
        int loc = getUniformLocation(name);

        if (loc > -1) {
            rlEnableShader(rlId);
            rlSetUniform(loc, &value, RL_SHADER_UNIFORM_FLOAT, 1);
        }
    }

    void Shader::setUniformInt(const String& name, int value) {
        unsigned int rlId = static_cast<unsigned int>(reinterpret_cast<uintptr_t>(mHandle));
        int loc = getUniformLocation(name);

        if (loc > -1) {
            rlEnableShader(rlId);
            rlSetUniform(loc, &value, RL_SHADER_UNIFORM_INT, 1);
        }
    }

    void Shader::setUniformUInt(const String& name, unsigned int value) {
        unsigned int rlId = static_cast<unsigned int>(reinterpret_cast<uintptr_t>(mHandle));
        int loc = getUniformLocation(name);

        if (loc > -1) {
            rlEnableShader(rlId);
            rlSetUniform(loc, &value, RL_SHADER_UNIFORM_UINT, 1);
        }
    }

    void Shader::setUniformVec2(const String& name, math::Vec2 value) {
        unsigned int rlId = static_cast<unsigned int>(reinterpret_cast<uintptr_t>(mHandle));
        int loc = getUniformLocation(name);

        if (loc > -1) {
            float rawValue[2] = { value.x, value.y };

            rlEnableShader(rlId);
            rlSetUniform(loc, &rawValue, RL_SHADER_UNIFORM_VEC2, 1);
        }
    }

    void Shader::setUniformVec3(const String& name, math::Vec3 value) {
        unsigned int rlId = static_cast<unsigned int>(reinterpret_cast<uintptr_t>(mHandle));
        int loc = getUniformLocation(name);

        if (loc > -1) {
            float rawValue[3] = {value.x, value.y, value.z};

            rlEnableShader(rlId);
            rlSetUniform(loc, &rawValue, RL_SHADER_UNIFORM_VEC3, 1);
        }
    }

    void Shader::setUniformVec4(const String& name, math::Vec4 value) {
        unsigned int rlId = static_cast<unsigned int>(reinterpret_cast<uintptr_t>(mHandle));
        int loc = getUniformLocation(name);

        if (loc > -1) {
            float rawValue[4] = {value.x, value.y, value.z, value.w};

            rlEnableShader(rlId);
            rlSetUniform(loc, &rawValue, RL_SHADER_UNIFORM_VEC4, 1);
        }
    }

    void Shader::setUniformVec2I(const String& name, math::Vec2I value) {
        unsigned int rlId = static_cast<unsigned int>(reinterpret_cast<uintptr_t>(mHandle));
        int loc = getUniformLocation(name);

        if (loc > -1) {
            int rawValue[2] = {value.x, value.y};

            rlEnableShader(rlId);
            rlSetUniform(loc, &rawValue, RL_SHADER_UNIFORM_IVEC2, 1);
        }
    }

    void Shader::setUniformVec3I(const String& name, math::Vec3I value) {
        unsigned int rlId = static_cast<unsigned int>(reinterpret_cast<uintptr_t>(mHandle));
        int loc = getUniformLocation(name);

        if (loc > -1) {
            int rawValue[3] = {value.x, value.y, value.z};

            rlEnableShader(rlId);
            rlSetUniform(loc, &rawValue, RL_SHADER_UNIFORM_IVEC3, 1);
        }
    }

    void Shader::setUniformVec4I(const String& name, math::Vec4I value) {
        unsigned int rlId = static_cast<unsigned int>(reinterpret_cast<uintptr_t>(mHandle));
        int loc = getUniformLocation(name);

        if (loc > -1) {
            int rawValue[4] = {value.x, value.y, value.z, value.w};

            rlEnableShader(rlId);
            rlSetUniform(loc, &rawValue, RL_SHADER_UNIFORM_IVEC4, 1);
        }
    }

    void Shader::setUniformMatrix4(const String& name, math::Matrix4 value) {
        unsigned int rlId = static_cast<unsigned int>(reinterpret_cast<uintptr_t>(mHandle));
        int loc = getUniformLocation(name);

        if (loc > -1) {
            ::Matrix matrix; // i genuinely hate rlgl for this
            for (int i = 0; i < 16; i++) reinterpret_cast<float*>(&matrix)[i] = value.m[i];

            rlEnableShader(rlId);
            rlSetUniformMatrix(loc, matrix);
        }
    }

    void InitWindow(int width, int height, const char* title) {
        ::SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN | FLAG_MSAA_4X_HINT);
        ::InitWindow(width, height, title);
        ::SetExitKey(KEY_NULL);
        ::SetTargetFPS(0);
    }

    void CloseWindow() {
        ::CloseWindow();
    }

    int GetWindowWidth() {
        return ::GetScreenWidth();
    }

    int GetWindowHeight() {
        return ::GetScreenHeight();
    }

    SharedPtr<Shader> CompileShader(const char* vShaderCode, const char* fShaderCode) {
        static HashMap<String, WeakPtr<Shader>> cache;
        static std::mutex cacheMutex;

        String key = String(vShaderCode) + "||" + fShaderCode;

        {
            std::lock_guard lock(cacheMutex);

            auto it = cache.find(key);
            if (it != cache.end()) {
                SharedPtr<Shader> shader = it->second.lock();
                if (shader != nullptr) {
                    return shader;
                }
            }
        }

        unsigned int rlId = rlLoadShaderCode(vShaderCode, fShaderCode);
        if (rlId == 0) return nullptr;

        SharedPtr<Shader> shader = MakeShared<Shader>(reinterpret_cast<void*>(rlId));

        {
            std::lock_guard lock(cacheMutex);
            cache[key] = shader;
        }

        return shader;
    }

    bool IsCursorVisible() {
        return !::IsCursorHidden();
    }

    void SetCursorVisible(bool visible) {
        if (visible) {
            if (!IsCursorVisible()) ::EnableCursor();
        } else {
            if (IsCursorVisible()) ::DisableCursor();
        }
    }

    void BeginDrawing() {
        ::BeginDrawing();
    }

    void EndDrawing() {
        ::EndDrawing();
    }

    void Begin3D(math::Vec3 position, math::Vec3 target, math::Vec3 up, float fovY, int projection) {
        rlDrawRenderBatchActive();

        rlMatrixMode(RL_PROJECTION);
        rlPushMatrix();
        rlLoadIdentity();

        float aspect = static_cast<float>(GetScreenWidth()) / static_cast<float>(GetScreenHeight());

        switch (static_cast<components::Camera::Projection>(projection)) {
            case components::Camera::Projection::Perspective: {
                double top = rlGetCullDistanceNear() * std::tan(math::Deg2Rad(fovY * 0.5));
                double right = top * aspect;

                rlFrustum(-right, right, -top, top, rlGetCullDistanceNear(), rlGetCullDistanceFar());
                break;
            }
            case components::Camera::Projection::Orthographic: {
                double top = fovY / 2.0;
                double right = top * aspect;

                rlOrtho(-right, right, -top, top, rlGetCullDistanceNear(), rlGetCullDistanceFar());

                break;
            }
        }

        rlMatrixMode(RL_MODELVIEW);
        rlLoadIdentity();

        math::Matrix4 view = math::Matrix4::lookAt(position, target, up);
        rlMultMatrixf(view.m);

        rlEnableDepthTest();
    }

    void End3D() {
        rlDrawRenderBatchActive();

        rlMatrixMode(RL_PROJECTION);
        rlPopMatrix();

        rlMatrixMode(RL_MODELVIEW);
        rlLoadIdentity();

        float scaleX = static_cast<float>(GetRenderWidth()) / static_cast<float>(GetScreenWidth());
        float scaleY = static_cast<float>(GetRenderHeight()) / static_cast<float>(GetScreenHeight());

        math::Matrix4 screenScale = math::Matrix4::scale({scaleX, scaleY, 1.0});

        if (rlGetActiveFramebuffer() == 0) rlMultMatrixf(screenScale.m);

        rlDisableDepthTest();
    }

    void ClearWindow() {
        rlClearColor(255, 255, 255, 255);
        rlClearScreenBuffers();
    }

    void DrawCube(math::Vec3 position, math::Vec3 size, math::Quat rotation, math::Color color) {
        rlPushMatrix();

        math::Matrix4 matrix = math::Matrix4::translation(position) * math::Matrix4::rotation(rotation) * math::Matrix4::scale(size);
        rlMultMatrixf(matrix.m);

        rlBegin(RL_TRIANGLES);
        rlColor4ub(color.r, color.g, color.b, color.a);

        // Front face (z+)
        rlNormal3f(0.0f, 0.0f, 1.0f);
        rlVertex3f(-0.5f, -0.5f,  0.5f);
        rlVertex3f( 0.5f, -0.5f,  0.5f);
        rlVertex3f( 0.5f,  0.5f,  0.5f);

        rlVertex3f(-0.5f, -0.5f,  0.5f);
        rlVertex3f( 0.5f,  0.5f,  0.5f);
        rlVertex3f(-0.5f,  0.5f,  0.5f);

        // Back face (z-)
        rlNormal3f(0.0f, 0.0f, -1.0f);
        rlVertex3f(-0.5f, -0.5f, -0.5f);
        rlVertex3f(-0.5f,  0.5f, -0.5f);
        rlVertex3f( 0.5f,  0.5f, -0.5f);

        rlVertex3f(-0.5f, -0.5f, -0.5f);
        rlVertex3f( 0.5f,  0.5f, -0.5f);
        rlVertex3f( 0.5f, -0.5f, -0.5f);

        // Top face (y+)
        rlNormal3f(0.0f, 1.0f, 0.0f);
        rlVertex3f(-0.5f,  0.5f, -0.5f);
        rlVertex3f(-0.5f,  0.5f,  0.5f);
        rlVertex3f( 0.5f,  0.5f,  0.5f);

        rlVertex3f(-0.5f,  0.5f, -0.5f);
        rlVertex3f( 0.5f,  0.5f,  0.5f);
        rlVertex3f( 0.5f,  0.5f, -0.5f);

        // Bottom face (y-)
        rlNormal3f(0.0f, -1.0f, 0.0f);
        rlVertex3f(-0.5f, -0.5f, -0.5f);
        rlVertex3f( 0.5f, -0.5f, -0.5f);
        rlVertex3f( 0.5f, -0.5f,  0.5f);

        rlVertex3f(-0.5f, -0.5f, -0.5f);
        rlVertex3f( 0.5f, -0.5f,  0.5f);
        rlVertex3f(-0.5f, -0.5f,  0.5f);

        // Right face (x+)
        rlNormal3f(1.0f, 0.0f, 0.0f);
        rlVertex3f(0.5f, -0.5f, -0.5f);
        rlVertex3f(0.5f,  0.5f, -0.5f);
        rlVertex3f(0.5f,  0.5f,  0.5f);

        rlVertex3f(0.5f, -0.5f, -0.5f);
        rlVertex3f(0.5f,  0.5f,  0.5f);
        rlVertex3f(0.5f, -0.5f,  0.5f);

        // Left face (x-)
        rlNormal3f(-1.0f, 0.0f, 0.0f);
        rlVertex3f(-0.5f, -0.5f, -0.5f);
        rlVertex3f(-0.5f, -0.5f,  0.5f);
        rlVertex3f(-0.5f,  0.5f,  0.5f);

        rlVertex3f(-0.5f, -0.5f, -0.5f);
        rlVertex3f(-0.5f,  0.5f,  0.5f);
        rlVertex3f(-0.5f,  0.5f, -0.5f);

        rlEnd();

        rlPopMatrix();

    }
}
