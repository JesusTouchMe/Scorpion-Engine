// Copyright 2025 JesusTouchMe

#ifndef SCORPION_MATH_H
#define SCORPION_MATH_H 1

namespace scorpion::math {
    struct Vec2 {
        float x, y;

        Vec2() : Vec2(0, 0) {}
        Vec2(float x, float y) : x(x), y(y) {}

        Vec2 operator+(Vec2 other) const {
            return {x + other.x, y + other.y};
        }

        Vec2 operator-(Vec2 other) const {
            return {x - other.x, y - other.y};
        }

        Vec2 operator*(Vec2 other) const {
            return {x * other.x, y * other.y};
        }

        Vec2 operator*(float scale) const {
            return {x * scale, y * scale};
        }

        Vec2 operator/(Vec2 other) const {
            return {x / other.x, y / other.y};
        }
    };

    struct Vec3 {
        float x, y, z;

        Vec2(float x, float y, float z) : x(x), y(y), z(z) {}
    };
}

#endif //SCORPION_MATH_H