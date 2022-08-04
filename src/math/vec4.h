#pragma once

struct Vec4
{
    union
    {
        struct
        {
            float x;
            float y;
            float z;
            float w;
        };
        struct
        {
            float a;
            float r;
            float g;
            float b;
        };
        float units[4];
    };
    Vec4(float x, float y, float z, float w);
    Vec4() = default;
    float length() const;
    Vec4 normalize() const;
    Vec4 add(const Vec4 other) const;
    Vec4 subst(const Vec4 other) const;
    Vec4 mul(float value) const;
    float dot(const Vec4 other) const;
    bool equals(const Vec4 other) const;

    Vec4 operator+(const Vec4 other) const;
    Vec4& operator+=(const Vec4 other);
    Vec4 operator-(const Vec4 other) const;
    Vec4 &operator-=(const Vec4 other);
    Vec4 operator*(float value) const;
    Vec4 &operator*=(float value);
    float operator*(const Vec4 other) const;
    bool operator==(const Vec4 other) const;
    bool operator!=(const Vec4 other) const;
};
