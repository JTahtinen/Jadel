#pragma once

struct Vec3
{
    union
    {
        struct
        {
            float x;
            float y;
            float z;
        };
        float units[3];
    };
    Vec3(float x, float y, float z);
    Vec3() = default;
    float length() const;
    Vec3 normalize() const;
    Vec3 add(const Vec3 other) const;
    Vec3 subst(const Vec3 other) const;
    Vec3 mul(float value) const;
    float dot(const Vec3 other) const;
    Vec3 cross(const Vec3 other) const;
    bool equals(const Vec3 other) const;

    Vec3 operator+(const Vec3 other) const;
    Vec3& operator+=(const Vec3 other);
    Vec3 operator-(const Vec3 other) const;
    Vec3 &operator-=(const Vec3 other);
    Vec3 operator*(float value) const;
    Vec3 &operator*=(float value);
    float operator*(const Vec3 other) const;
    bool operator==(const Vec3 other) const;
    bool operator!=(const Vec3 other) const;
};
