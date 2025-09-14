// Copyright 2025 JesusTouchMe

#include "scorpion/render/renderer.h"

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

    void BeginDrawing() {
        ::BeginDrawing();
    }

    void EndDrawing() {
        ::EndDrawing();
    }

    void Begin3D(math::Vec3 position, math::Vec3 target, math::Vec3 up, float fovY, int projection) {
        ::Camera3D rlCam = {
            .position = { .x = position.x, .y = position.y, .z = position.z },
            .target = { .x = target.x, .y = target.y, .z = target.z },
            .up = { .x = up.x, .y = up.y, .z = up.z },
            .fovy = fovY,
            .projection = projection,
        };

        ::BeginMode3D(rlCam);
    }

    void End3D() {
        ::EndMode3D();
    }

    void ClearWindow() {
        ::ClearBackground(WHITE);
    }

    void DrawCube(math::Vec3 position, math::Vec3 size, math::Quat rotation, math::Color color) {
        rlPushMatrix();

        rlTranslatef(position.x, position.y, position.z);

        math::Matrix4 matrix = math::Matrix4::rotation(rotation);
        rlMultMatrixf(matrix.m);

        rlScalef(size.x, size.y, size.z);

        rlBegin(RL_TRIANGLES);
        rlColor4ub(color.r, color.g, color.b, color.a);

        rlVertex3f(-0.5f, -0.5f, 0.5f);
        rlVertex3f( 0.5f, -0.5f, 0.5f);
        rlVertex3f( 0.5f,  0.5f, 0.5f);

        rlVertex3f(-0.5f, -0.5f, 0.5f);
        rlVertex3f( 0.5f,  0.5f, 0.5f);
        rlVertex3f(-0.5f,  0.5f, 0.5f);

        // back face
        rlVertex3f(-0.5f, -0.5f, -0.5f);
        rlVertex3f(-0.5f,  0.5f, -0.5f);
        rlVertex3f( 0.5f,  0.5f, -0.5f);

        rlVertex3f(-0.5f, -0.5f, -0.5f);
        rlVertex3f( 0.5f,  0.5f, -0.5f);
        rlVertex3f( 0.5f, -0.5f, -0.5f);

        // top face
        rlVertex3f(-0.5f, 0.5f, -0.5f);
        rlVertex3f(-0.5f, 0.5f,  0.5f);
        rlVertex3f( 0.5f, 0.5f,  0.5f);

        rlVertex3f(-0.5f, 0.5f, -0.5f);
        rlVertex3f( 0.5f, 0.5f,  0.5f);
        rlVertex3f( 0.5f, 0.5f, -0.5f);

        // bottom face
        rlVertex3f(-0.5f, -0.5f, -0.5f);
        rlVertex3f( 0.5f, -0.5f, -0.5f);
        rlVertex3f( 0.5f, -0.5f,  0.5f);

        rlVertex3f(-0.5f, -0.5f, -0.5f);
        rlVertex3f( 0.5f, -0.5f,  0.5f);
        rlVertex3f(-0.5f, -0.5f,  0.5f);

        // right face
        rlVertex3f(0.5f, -0.5f, -0.5f);
        rlVertex3f(0.5f,  0.5f, -0.5f);
        rlVertex3f(0.5f,  0.5f,  0.5f);

        rlVertex3f(0.5f, -0.5f, -0.5f);
        rlVertex3f(0.5f,  0.5f,  0.5f);
        rlVertex3f(0.5f, -0.5f,  0.5f);

        // left face
        rlVertex3f(-0.5f, -0.5f, -0.5f);
        rlVertex3f(-0.5f, -0.5f,  0.5f);
        rlVertex3f(-0.5f,  0.5f,  0.5f);

        rlVertex3f(-0.5f, -0.5f, -0.5f);
        rlVertex3f(-0.5f,  0.5f,  0.5f);
        rlVertex3f(-0.5f,  0.5f, -0.5f);

        rlEnd();

        /*
        rlBegin(RL_LINES);
        rlColor4ub(0, 0, 0, 255);

        math::Vec3 verts[8] = {
            {-0.5f, -0.5f, -0.5f}, {0.5f, -0.5f, -0.5f},
            {0.5f, 0.5f, -0.5f}, {-0.5f, 0.5f, -0.5f},
            {-0.5f, -0.5f, 0.5f}, {0.5f, -0.5f, 0.5f},
            {0.5f, 0.5f, 0.5f}, {-0.5f, 0.5f, 0.5f}
        };

        int edges[12][2] = {
            {0, 1}, {1, 2}, {2, 3}, {3, 0},
            {4, 5}, {5, 6}, {6, 7}, {7, 4},
            {0, 4}, {1, 5}, {2, 6}, {3, 7}
        };

        for (int i = 0; i < 12; i++) {
            rlVertex3f(verts[edges[i][0]].x, verts[edges[i][0]].y, verts[edges[i][0]].z);
            rlVertex3f(verts[edges[i][1]].x, verts[edges[i][1]].y, verts[edges[i][1]].z);
        }

        rlEnd();
        */

        rlPopMatrix();
    }
}
