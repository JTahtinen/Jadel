#pragma once
#include "vec4.h"
#include "vec3.h"
struct Mat4
{
    float units[16];

    Vec4 mul(const Vec4 &vec) const;
    Vec3 mul(const Vec3 &vec) const;
    Mat4 mul(const Mat4& other) const;
    static Mat4 identity();
    static Mat4 perspective(float fov, float aspect, float near, float far);
    static Mat4 translate(const Vec3 &translation);
    static Mat4 rotation(float angle, const Vec3 &axis);
    static Mat4 scale(const Vec3 &scalar);
    static Mat4 ortho(float left, float right, float top, float bottom, float near, float far);
    Mat4 operator*(const Mat4& other) const;
    Vec4 operator*(const Vec4& vec) const;
    Vec3 operator*(const Vec3& vec) const;
};
