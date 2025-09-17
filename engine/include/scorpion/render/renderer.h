// Copyright 2025 JesusTouchMe

#ifndef SCORPION_RENDERER_H
#define SCORPION_RENDERER_H 1

#include "scorpion/core/api.h"

#include "scorpion/util/math.h"
#include "scorpion/util/std_types.h"

// This whole module exists only to make the potential future transition away from raylib a bit easier on the soul
namespace scorpion::render {
    class SCORPION_API Shader {
    public:
        Shader(void* handle);
        ~Shader();

        void begin();
        void end();

        int getUniformLocation(const String& name);
        int getAttribLocation(const String& name);

        void setUniformFloat(const String& name, float value);
        void setUniformInt(const String& name, int value);
        void setUniformUInt(const String& name, unsigned int value);
        void setUniformVec2(const String& name, math::Vec2 value);
        void setUniformVec3(const String& name, math::Vec3 value);
        void setUniformVec4(const String& name, math::Vec4 value);
        void setUniformVec2I(const String& name, math::Vec2I value);
        void setUniformVec3I(const String& name, math::Vec3I value);
        void setUniformVec4I(const String& name, math::Vec4I value);
        void setUniformMatrix4(const String& name, math::Matrix4 value);

    private:
        void* mHandle;
        void* mInternalState;
        HashMap<String, int> mUniformLocs; //NOTE: this is not fully backend-independent (some platforms use pointers and other shit, but we only have rlgl int for now)
        HashMap<String, int> mAttribLocs;
        bool mBegun = false;
    };

    SCORPION_API void InitWindow(int width, int height, const char* title);
    SCORPION_API void CloseWindow();

    SCORPION_API int GetWindowWidth();
    SCORPION_API int GetWindowHeight();

    SCORPION_API SharedPtr<Shader> CompileShader(const char* vShaderCode, const char* fShaderCode);

    SCORPION_API bool IsCursorVisible();
    SCORPION_API void SetCursorVisible(bool visible);

    SCORPION_API void BeginDrawing();
    SCORPION_API void EndDrawing();

    SCORPION_API void Begin3D(math::Vec3 position, math::Vec3 target, math::Vec3 up, float fovY, int projection);
    SCORPION_API void End3D();

    SCORPION_API void ClearWindow();

    SCORPION_API void DrawCube(math::Vec3 position, math::Vec3 size, math::Quat rotation, math::Color color);
}

#endif // SCORPION_RENDERER_H
