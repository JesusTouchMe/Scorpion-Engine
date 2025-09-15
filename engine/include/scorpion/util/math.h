// Copyright 2025 JesusTouchMe

#ifndef SCORPION_MATH_H
#define SCORPION_MATH_H 1

#include <cmath>
#include <cstdint>
#include <numbers>

namespace scorpion::math {
    struct Matrix4;

    struct Vec2 {
        float x, y;

        static const Vec2 zero;
        static const Vec2 one;

        Vec2() : Vec2(0, 0) {}
        Vec2(float x, float y) : x(x), y(y) {}

        Vec2 operator-() const {
            return Vec2(-x, -y);
        }

        Vec2 operator+(const Vec2& other) const {
            return {x + other.x, y + other.y};
        }

        Vec2 operator-(const Vec2& other) const {
            return {x - other.x, y - other.y};
        }

        Vec2 operator*(const Vec2& other) const {
            return {x * other.x, y * other.y};
        }

        Vec2 operator*(float scale) const {
            return {x * scale, y * scale};
        }

        Vec2 operator/(const Vec2& other) const {
            return {x / other.x, y / other.y};
        }

        Vec2 operator/(float scale) const {
            return {x / scale, y / scale};
        }

        float length() const { return std::sqrt(x * x + y * y); }
        float lengthSquared() const { return x * x + y * y; }

        Vec2 normalized() const {
            float len = length();
            return len == 0 ? Vec2(0, 0) : Vec2(x / len, y / len);
        }

        float dot(const Vec2& other) const { return x * other.x + y * other.y; }
    };

    inline const Vec2 Vec2::zero = {0, 0};
    inline const Vec2 Vec2::one = {1, 1};

    struct Vec3 {
        float x, y, z;

        static const Vec3 zero;
        static const Vec3 one;

        Vec3() : Vec3(0, 0, 0) {}
        Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

        Vec3 operator-() const {
            return {-x, -y, -z};
        }

        Vec3 operator+(const Vec3& other) const {
            return {x + other.x, y + other.y, z + other.z};
        }

        Vec3 operator-(const Vec3& other) const {
            return {x - other.x, y - other.y, z - other.z};
        }

        Vec3 operator*(const Vec3& other) const {
            return {x * other.x, y * other.y, z * other.z};
        }

        Vec3 operator*(float scale) const {
            return {x * scale, y * scale, z * scale};
        }

        Vec3 operator/(const Vec3& other) const {
            return {x / other.x, y / other.y, z / other.z};
        }

        Vec3 operator/(float scale) const {
            return {x / scale, y / scale, z / scale};
        }

        Vec3& operator+=(const Vec3& other) {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        Vec3& operator-=(const Vec3& other) {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            return *this;
        }

        Vec3& operator*=(const Vec3& other) {
            x *= other.x;
            y *= other.y;
            z *= other.z;
            return *this;
        }

        Vec3& operator*=(float scale) {
            x *= scale;
            y *= scale;
            z *= scale;
            return *this;
        }

        Vec3& operator/=(const Vec3& other) {
            x /= other.x;
            y /= other.y;
            z /= other.z;
            return *this;
        }

        Vec3& operator/=(float scale) {
            x /= scale;
            y /= scale;
            z /= scale;
            return *this;
        }

        float length() const { return std::sqrt(x * x + y * y + z * z); }
        float lengthSquared() const { return x * x + y * y + z * z; }

        Vec3 normalized() const {
            float len = length();
            return len == 0 ? zero : Vec3(x / len, y / len, z / len);
        }

        float dot(const Vec3& v) const { return x * v.x + y * v.y + z * v.z; }

        Vec3 cross(const Vec3& v) const {
            return {
                y * v.z - z * v.y,
                z * v.x - x * v.z,
                x * v.y - y * v.x
            };
        }

        float angle(const Vec3& targetPos) const {
            float result = 0.0f;

            Vec3 cross = this->cross(targetPos);
            float len = cross.length();
            float dot = this->dot(targetPos);
            result = std::atan2(len, dot);

            return result;
        }

        Vec3 rotateByAxisAngle(Vec3 axis, float angle) const {
            Vec3 result = *this;

            float length = axis.length();
            if (length == 0.0f) length = 1.0f;

            float ilength = 1.0f / length;
            axis.x *= ilength;
            axis.y *= ilength;
            axis.z *= ilength;

            angle /= 2.0f;
            float a = std::sin(angle);
            float b = axis.x * a;
            float c = axis.y * a;
            float d = axis.z * a;
            a = std::cos(angle);
            Vec3 w = {b, c, d};
            Vec3 wv = w.cross(*this);
            Vec3 wwv = w.cross(wv);

            a *= 2;
            wv.x *= a;
            wv.y *= a;
            wv.z *= a;

            wwv *= 2;

            result += wv;
            result += wwv;

            return result;
        }
    };

    inline const Vec3 Vec3::zero = {0, 0, 0};
    inline const Vec3 Vec3::one = {1, 1, 1};

    struct Vec4 {
        float x, y, z, w;

        static const Vec4 zero;
        static const Vec4 one;

        Vec4() : Vec4(0, 0, 0, 0) {}
        Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

        Vec4 operator-() const {
            return {-x, -y, -z, -w};
        }

        Vec4 operator+(const Vec4& other) const {
            return {x + other.x, y + other.y, z + other.z, w + other.w};
        }

        Vec4 operator-(const Vec4& other) const {
            return {x - other.x, y - other.y, z - other.z, w - other.w};
        }

        Vec4 operator*(const Vec4& other) const {
            return {x * other.x, y * other.y, z * other.z, w * other.w};
        }

        Vec4 operator*(float scale) const {
            return {x * scale, y * scale, z * scale, w * scale};
        }

        Vec4 operator/(const Vec4& other) const {
            return {x / other.x, y / other.y, z / other.z, w / other.w};
        }

        Vec4 operator/(float scale) const {
            return {x / scale, y / scale, z / scale, w / scale};
        }

        float length() const { return std::sqrt(x * x + y * y + z * z); }
        float lengthSquared() const { return x * x + y * y + z * z; }

        Vec4 normalized() const {
            float len = length();
            return len == 0 ? zero : Vec4(x / len, y / len, z / len, w / len);
        }
    };

    inline const Vec4 Vec4::zero = {0, 0, 0, 0};
    inline const Vec4 Vec4::one = {1, 1, 1, 0};

    struct Vec2I {
        int x, y;

        static const Vec2I zero;
        static const Vec2I one;

        Vec2I() : Vec2I(0, 0) {}
        Vec2I(int x, int y) : x(x), y(y) {}

        Vec2I operator-() const {
            return {-x, -y};
        }

        Vec2I operator+(const Vec2I& other) const {
            return {x + other.x, y + other.y};
        }

        Vec2I operator-(const Vec2I& other) const {
            return {x - other.x, y - other.y};
        }

        Vec2I operator*(const Vec2I& other) const {
            return {x * other.x, y * other.y};
        }

        Vec2I operator/(const Vec2I& other) const {
            return {x / other.x, y / other.y};
        }

        Vec2I operator%(const Vec2I& other) const {
            return {x % other.x, y % other.y};
        }
    };

    inline const Vec2I Vec2I::zero = {0, 0};
    inline const Vec2I Vec2I::one = {1, 1};

    struct Vec3I {
        int x, y, z;

        static const Vec3I zero;
        static const Vec3I one;

        Vec3I() : Vec3I(0, 0, 0) {}
        Vec3I(int x, int y, int z) : x(x), y(y), z(z) {}

        Vec3I operator-() const {
            return {-x, -y, -z};
        }

        Vec3I operator+(const Vec3I& other) const {
            return {x + other.x, y + other.y, z + other.z};
        }

        Vec3I operator-(const Vec3I& other) const {
            return {x - other.x, y - other.y, z - other.z};
        }

        Vec3I operator*(const Vec3I& other) const {
            return {x * other.x, y * other.y, z * other.z};
        }

        Vec3I operator/(const Vec3I& other) const {
            return {x / other.x, y / other.y, z / other.z};
        }

        Vec3I operator%(const Vec3I& other) const {
            return {x % other.x, y % other.y, z % other.z};
        }
    };

    inline const Vec3I Vec3I::zero = {0, 0, 0};
    inline const Vec3I Vec3I::one = {1, 1, 1};

    struct Vec4I {
        int x, y, z, w;

        static const Vec4I zero;
        static const Vec4I one;

        Vec4I() : Vec4I(0, 0, 0, 0) {}
        Vec4I(int x, int y, int z, int w) : x(x), y(y), z(z), w(w) {}

        Vec4I operator-() const {
            return {-x, -y, -z, -w};
        }

        Vec4I operator+(const Vec4I& other) const {
            return {x + other.x, y + other.y, z + other.z, w + other.w};
        }

        Vec4I operator-(const Vec4I& other) const {
            return {x - other.x, y - other.y, z - other.z, w - other.w};
        }

        Vec4I operator*(const Vec4I& other) const {
            return {x * other.x, y * other.y, z * other.z, w * other.w};
        }

        Vec4I operator/(const Vec4I& other) const {
            return {x / other.x, y / other.y, z / other.z, w / other.w};
        }
    };

    inline const Vec4I Vec4I::zero = {0, 0, 0, 0};
    inline const Vec4I Vec4I::one = {1, 1, 1, 0};

    struct Quat {
        float w, x, y, z;

        static const Quat identity;

        Quat() : Quat(0, 0, 0, 0) {}
        Quat(float w, float x, float y, float z) : w(w), x(x), y(y), z(z) {}

        Vec3 operator*(const Vec3& v) const {
            Quat qv(0, v.x, v.y, v.z);
            Quat qConj(w, -x, -y, -z);
            Quat result = (*this) * qv * qConj;
            return {result.x, result.y, result.z};
        }

        Quat operator*(const Quat& other) const {
            return {
                w * other.w - x * other.x - y * other.y - z * other.z,
                w * other.x + x * other.w + y * other.z - z * other.y,
                w * other.y - x * other.z + y * other.w + z * other.x,
                w * other.z + x * other.y - y * other.x + z * other.w
            };
        }

        Quat normalized() const {
            float len = std::sqrt(w * w + x * x + y * y + z * z);
            if (len == 0) return identity;
            return {w / len, x / len, y / len, z / len};
        }

        static Quat fromAxisAngle(const Vec3& axis, float angleRad) {
            float half = angleRad / 2;
            float s = std::sin(half);
            return Quat(std::cos(half), axis.x * s, axis.y * s, axis.z * s).normalized();
        }

        static Quat fromMatrix(const Matrix4& matrix);
    };

    inline const Quat Quat::identity = {1, 0, 0, 0};

    struct Matrix4 {
        float m[16]{};

        Matrix4() {
            for (int i = 0; i < 16; i++) m[i] = 0;
        }

        Matrix4 operator*(const Matrix4& other) const {
            Matrix4 result;
            for (int row = 0; row < 4; ++row) {
                for (int col = 0; col < 4; ++col) {
                    result.m[col + row*4] =
                        m[row*4 + 0] * other.m[col + 0] +
                        m[row*4 + 1] * other.m[col + 4] +
                        m[row*4 + 2] * other.m[col + 8] +
                        m[row*4 + 3] * other.m[col + 12];
                }
            }
            return result;
        }

        static Matrix4 identity() {
            Matrix4 matrix;
            matrix.m[0] = matrix.m[5] = matrix.m[10] = matrix.m[15] = 1;
            return matrix;
        }

        static Matrix4 translation(const Vec3& translation) {
            Matrix4 matrix;
            matrix.m[12] = translation.x;
            matrix.m[13] = translation.y;
            matrix.m[14] = translation.z;
            return matrix;
        }

        static Matrix4 scale(const Vec3& scale) {
            Matrix4 matrix;
            matrix.m[0] = scale.x;
            matrix.m[5] = scale.y;
            matrix.m[10] = scale.z;
            return matrix;
        }

        static Matrix4 rotation(const Quat& rotation) {
            Matrix4 matrix = identity();

            float xx = rotation.x * rotation.x;
            float yy = rotation.y * rotation.y;
            float zz = rotation.z * rotation.z;
            float xy = rotation.x * rotation.y;
            float xz = rotation.x * rotation.z;
            float yz = rotation.y * rotation.z;
            float wx = rotation.w * rotation.x;
            float wy = rotation.w * rotation.y;
            float wz = rotation.w * rotation.z;

            matrix.m[0] = 1.0f - 2.0f * (yy + zz);
            matrix.m[1] = 2.0f * (xy + wz);
            matrix.m[2] = 2.0f * (xz - wy);
            matrix.m[3] = 0.0f;

            matrix.m[4] = 2.0f * (xy - wz);
            matrix.m[5] = 1.0f - 2.0f * (xx + zz);
            matrix.m[6] = 2.0f * (yz + wx);
            matrix.m[7] = 0.0f;

            matrix.m[8]  = 2.0f * (xz + wy);
            matrix.m[9]  = 2.0f * (yz - wx);
            matrix.m[10] = 1.0f - 2.0f * (xx + yy);
            matrix.m[11] = 0.0f;

            matrix.m[12] = 0.0f;
            matrix.m[13] = 0.0f;
            matrix.m[14] = 0.0f;
            matrix.m[15] = 1.0f;

            return matrix;
        }

        static Matrix4 lookAt(const Vec3& eye, const Vec3& target, const Vec3& up) {
            Matrix4 result;

            float length = 0.0f;
            float ilength = 0.0f;

            Vec3 vz = eye - target;
            Vec3 v = vz;

            length = v.length();
            if (length == 0.0f) length = 1.0f;

            ilength = 1.0f / length;
            vz.x *= ilength;
            vz.y *= ilength;
            vz.z *= ilength;

            Vec3 vx = up.cross(vz);
            v = vx;

            length = v.length();
            if (length == 0.0f) length = 1.0f;

            ilength = 1.0f / length;
            vx.x *= ilength;
            vx.y *= ilength;
            vx.z *= ilength;

            Vec3 vy = vz.cross(vx);

            result.m[0] = vx.x;
            result.m[1] = vy.x;
            result.m[2] = vz.x;
            result.m[3] = 0.0f;
            result.m[4] = vx.y;
            result.m[5] = vy.y;
            result.m[6] = vz.y;
            result.m[7] = 0.0f;
            result.m[8] = vx.z;
            result.m[9] = vy.z;
            result.m[10] = vz.z;
            result.m[11] = 0.0f;
            result.m[12] = -vx.dot(eye);
            result.m[13] = -vy.dot(eye);
            result.m[14] = -vz.dot(eye);
            result.m[15] = 1.0f;
        }
    };

    inline Quat Quat::fromMatrix(const Matrix4& matrix) {
        Quat q;
        float trace = matrix.m[0] + matrix.m[5] + matrix.m[10];

        if (trace > 0.0f) {
            float s = std::sqrt(trace + 1.0f) * 2.0f;
            q.w = 0.25f * s;
            q.x = (matrix.m[9] - matrix.m[6]) / s;
            q.y = (matrix.m[2] - matrix.m[8]) / s;
            q.z = (matrix.m[4] - matrix.m[1]) / s;
        } else if (matrix.m[0] > matrix.m[5] && matrix.m[0] > matrix.m[10]) {
            float s = std::sqrt(1.0f + matrix.m[0] - matrix.m[5] - matrix.m[10]) * 2.0f;
            q.w = (matrix.m[9] - matrix.m[6]) / s;
            q.x = 0.25f * s;
            q.y = (matrix.m[1] + matrix.m[4]) / s;
            q.z = (matrix.m[2] + matrix.m[8]) / s;
        } else if (matrix.m[5] > matrix.m[10]) {
            float s = std::sqrt(1.0f + matrix.m[5] - matrix.m[0] - matrix.m[10]) * 2.0f;
            q.w = (matrix.m[2] - matrix.m[8]) / s;
            q.x = (matrix.m[1] + matrix.m[4]) / s;
            q.y = 0.25f * s;
            q.z = (matrix.m[6] + matrix.m[9]) / s;
        } else {
            float s = std::sqrt(1.0f + matrix.m[10] - matrix.m[0] - matrix.m[5]) * 2.0f;
            q.w = (matrix.m[4] - matrix.m[1]) / s;
            q.x = (matrix.m[2] + matrix.m[8]) / s;
            q.y = (matrix.m[6] + matrix.m[9]) / s;
            q.z = 0.25f * s;
        }

        return q.normalized();
    }

    struct Color {
        uint8_t r, g, b, a;

        static const Color red;
        static const Color green;
        static const Color blue;
        static const Color white;
        static const Color black;
        static const Color transparent;

        static const Color gray;
        static const Color lightGray;
        static const Color darkGray;

        static const Color yellow;
        static const Color cyan;
        static const Color magenta;
        static const Color orange;
        static const Color purple;
        static const Color brown;
        static const Color pink;
        static const Color gold;
        static const Color lime;
        static const Color skyBlue;

        Vec3 toVec3() const {
            return {
                static_cast<float>(r) / 255,
                static_cast<float>(g) / 255,
                static_cast<float>(b) / 255
            };
        }
    };

    inline const Color Color::red = {255, 0, 0, 255};
    inline const Color Color::green = {0, 255, 0, 255};
    inline const Color Color::blue = {0, 0, 255, 255};
    inline const Color Color::white = {255, 255, 255, 255};
    inline const Color Color::black = {0, 0, 0, 255};
    inline const Color Color::transparent = {0, 0, 0, 0};

    inline const Color Color::gray = {128, 128, 128, 255};
    inline const Color Color::lightGray = {200, 200, 200, 255};
    inline const Color Color::darkGray = {64, 64, 64, 255};

    inline const Color Color::yellow = {255, 255, 0, 255};
    inline const Color Color::cyan = {0, 255, 255, 255};
    inline const Color Color::magenta = {255, 0, 255, 255};
    inline const Color Color::orange = {255, 165, 0, 255};
    inline const Color Color::purple = {128, 0, 128, 255};
    inline const Color Color::brown = {165, 42, 42, 255};
    inline const Color Color::pink = {255, 192, 203, 255};
    inline const Color Color::gold = {255, 215, 0, 255};
    inline const Color Color::lime = {50, 205, 50, 255};
    inline const Color Color::skyBlue = {135, 206, 235, 255};

    constexpr inline float Deg2Rad(float deg) {
        return deg * static_cast<float>(std::numbers::pi) / 180.0f;
    }

    constexpr inline double Deg2Rad(double deg) {
        return deg * std::numbers::pi / 180.0;
    }
}

#endif //SCORPION_MATH_H