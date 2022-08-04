#include "mat4.h"
#include "math.h"

#define GET(x, y) units[x + y * 4]
#define GETOTHER(x, y) other.units[x + y * 4]


Vec4 Mat4::mul(const Vec4 &vec) const
{
    /*
    Vec4 result(0, 0, 0, 0);

    for (int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            result.units[i] += GET(j, i) * vec.units[j];
        }
    }
    return result;
*/

        
    
    Vec4 result(    
        GET(0, 0) * vec.x + GET(1, 0) * vec.y + GET(2, 0) * vec.z + GET(3, 0) * vec.w,
        GET(0, 1) * vec.x + GET(1, 1) * vec.y + GET(2, 1) * vec.z + GET(3, 1) * vec.w,
        GET(0, 2) * vec.x + GET(1, 2) * vec.y + GET(2, 2) * vec.z + GET(3, 2) * vec.w,
        GET(0, 3) * vec.x + GET(1, 3) * vec.y + GET(2, 3) * vec.z + GET(3, 3) * vec.w);
    return result;
/*
    /*return Vec4{
				GET(0, 0) * vec.x + GET(0, 1) * vec.y + GET(0, 2) * vec.z + GET(0, 3) * vec.w,
				GET(1, 0) * vec.x + GET(1, 1) * vec.y + GET(2, 2) * vec.z + GET(3, 3) * vec.w,
				GET(2, 0) * vec.x + GET(1, 1) * vec.y + GET(2, 2) * vec.z + GET(3, 3) * vec.w,
				GET(3, 0) * vec.x + GET(1, 1) * vec.y + GET(2, 2) * vec.z + GET(3, 3) * vec.w
			};*/
}

Vec3 Mat4::mul(const Vec3 &vec) const
{
    /*
    Vec3 result(0, 0, 0);
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            result.units[i] += GET(j, i) * vec.units[j];
        }
    }
    return result;
    */
    
    Vec3 result(
        GET(0, 0) * vec.x + GET(1, 0) * vec.y + GET(2, 0) * vec.z + GET(3, 0),
        GET(0, 1) * vec.x + GET(1, 1) * vec.y + GET(2, 1) * vec.z + GET(3, 1),
        GET(0, 2) * vec.x + GET(1, 2) * vec.y + GET(2, 2) * vec.z + GET(3, 2));
    return result;
    
    /*return Vec3{
				GET(0, 0) * vec.x + GET(0, 1) * vec.y + GET(0, 2) * vec.z + GET(0, 3),
				GET(1, 0) * vec.x + GET(1, 1) * vec.y + GET(2, 2) * vec.z + GET(3, 3),
				GET(2, 0) * vec.x + GET(1, 1) * vec.y + GET(2, 2) * vec.z + GET(3, 3)
			};*/
}

Mat4 Mat4::mul(const Mat4& other) const
{
    Mat4 result;
    for (int row = 0; row < 4; ++row)
    {
        for (int column = 0; column < 4; ++column)
        {
            result.units[column + row * 4] = 
                GET(0, row) * other.GET(column, 0) + 
                GET(1, row) * other.GET(column, 1) + 
                GET(2, row) * other.GET(column, 2) +
                GET(3, row) * other.GET(column, 3);            
        }
    }
    return result;
}

Mat4 Mat4::identity()
{
    return {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f};
}

Mat4 Mat4::perspective(float fov, float aspect, float near, float far)
{
    float fovRad = TO_RADIANS(fov);
    float scale = 1.0f / (aspect * (float)tan(fovRad / 2.0f));

    Mat4 result =
    {
        scale, 0, 0, 0,
        0, scale, 0, 0,
        0, 0, -far / (far - near), -far * near / (far - near),
        0, 0, -1.0f, 0

    };
    return result;
/*
    return Mat4{
        scale, 0, 0, 0,
        0, scale, 0, 0,
        0, 0, -((far + near) / (far - near)), -((2.0f * (near * far)) / (far - near)),
        0, 0, -1.0f, 0};
*/
}

Mat4 Mat4::translate(const Vec3 &translation)
{
    return {
        1.0f, 0.0f, 0.0f, translation.x,
        0.0f, 1.0f, 0.0f, translation.y,
        0.0f, 0.0f, 1.0f, translation.z,
        0.0f, 0.0f, 0.0f, 1.0f};
}

Mat4 Mat4::rotation(float angleInDeg, const Vec3 &axis)
{
    float A = TO_RADIANS(angleInDeg);
    float x = axis.x;
    float y = axis.y;
    float z = axis.z;
    float c = cos(A);
    float s = sin(A);
    float mc = (1.0f - c);

    return Mat4{
        x * x * mc + c, x * y * mc - z * s, x * z * mc + y * s, 0,
        x * y * mc + z * s, y * y * mc + c, y * z * mc - x * s, 0,
        x * z * mc - y * s, y * z * mc + x * s, z * z * mc + c, 0,
        0, 0, 0, 1};
}

Mat4 Mat4::scale(const Vec3 &scalar)
{
    return Mat4{
        scalar.x, 0.0f, 0.0f, 0.0f,
        0.0f, scalar.y, 0.0f, 0.0f,
        0.0f, 0.0f, scalar.z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f};
}

Mat4 Mat4::ortho(float left, float right, float top, float bottom, float near, float far)
{
    return Mat4{
        2.0f / (right - left), 0, 0, -((right + left) / (right - left)),
        0.0f, 2 / (top - bottom), 0.0f, -((top + bottom) / (top - bottom)),
        0.0f, 0.0f, (-2.0f) / (far - near), -((far + near) / (far - near)),
        0.0f, 0.0f, 0.0f, 1.0f};
}

Mat4 Mat4::operator*(const Mat4& other) const
{
    return mul(other);
}

Vec4 Mat4::operator*(const Vec4& vec) const
{
    return mul(vec);
}

Vec3 Mat4::operator*(const Vec3& vec) const
{
    return mul(vec);
}
