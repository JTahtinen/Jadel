#include "mat3.h"
#include "math.h"

#define GET(x, y) units[x + y * 3]

Mat3::Mat3(float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2)
{
    units[0] = x0;
    units[1] = y0;
    units[2] = z0;
    units[3] = x1;
    units[4] = y1;
    units[5] = z1;
    units[6] = x2; 
    units[7] = y2;
    units[8] = z2;
}

Vec2 Mat3::mul(const Vec2 vec) const
{
    Vec2 result(vec.x * units[0] + vec.y * units[1] + 1.0f * units[2],
                vec.x * units[3] + vec.y * units[4] + 1.0f * units[5]);
    return result;
}

Mat3 Mat3::mul(const Mat3& other) const
{
    Mat3 result;
    for (int row = 0; row < 3; ++row)
    {
        for (int column = 0; column < 3; ++column)
        {
            result.units[column + row * 3] = 
            GET(0, row) * other.GET(column, 0) + 
            GET(1, row) * other.GET(column, 1) + 
            GET(2, row) * other.GET(column, 2);
        }
    }
    return result;
   /*Mat3 result = {
                GET(0,0) * other.GET(0,0) + GET(1,0) * other.GET(0,1) + GET(2,0) * other.GET(0,2),
				GET(0,0) * other.GET(1,0) + GET(1,0) * other.GET(1,1) + GET(2,0) * other.GET(1,2),
				GET(0,0) * other.GET(2,0) + GET(1,0) * other.GET(2,1) + GET(2,0) * other.GET(2,2),
				

				// Second row
				GET(0,1) * other.GET(0,0) + GET(1,1) * other.GET(0,1) + GET(2,1) * other.GET(0,2),
				GET(0,1) * other.GET(1,0) + GET(1,1) * other.GET(1,1) + GET(2,1) * other.GET(1,2),
				GET(0,1) * other.GET(2,0) + GET(1,1) * other.GET(2,1) + GET(2,1) * other.GET(2,2),
				

				// Third row
				GET(0,2) * other.GET(0,0) + GET(1,2) * other.GET(0,1) + GET(2,2) * other.GET(0,2),
				GET(0,2) * other.GET(1,0) + GET(1,2) * other.GET(1,1) + GET(2,2) * other.GET(1,2),
				GET(0,2) * other.GET(2,0) + GET(1,2) * other.GET(2,1) + GET(2,2) * other.GET(2,2),

                };			
    return result;*/
}

Mat3 Mat3::identity()
{
    Mat3 result(1.0f, 0.0f, 0.0f,
                    0.0f, 1.0f, 0.0f,
                    0.0f, 0.0f, 1.0f);
    return result;
}

Mat3 Mat3::rotation(float angle)
{
    Mat3 result(cosf(angle), -sinf(angle), 0,
                    sinf(angle), cosf(angle), 0,
                    0, 0, 1.0f);
    return result;
}

Mat3 Mat3::translation(Vec2 vec)
{  
    Mat3 result(1.0f, 0, vec.x,
                   0, 1.0f, vec.y,
                   0, 0, 1.0f);
    return result;
}

Mat3 Mat3::scale(Vec2 amount)
{
    Mat3 result(amount.x, 0, 0,
                0, amount.y, 0,
                0, 0, 1.0f);
    return result;
}

Mat3 Mat3::view(Vec2 pos, float angle, float scalar, float aspect)
{
    Mat3 trans = translation(pos);
    Mat3 rot = rotation(angle);
    Mat3 asp = scale(Vec2(1.0f, aspect));
    Mat3 sc = scale(Vec2(scalar, scalar));
    Mat3 result = (sc * asp * rot * trans);
    //Mat3 result = trans * rot * sc * asp;
    return result;
}

Mat3 Mat3::operator*(const Mat3& other) const
{
    return this->mul(other);
}

Vec2 Mat3::operator*(const Vec2 vec) const
{
    return this->mul(vec);
}

float Mat3::operator[](unsigned int index) const
{
    return units[index];
}

float& Mat3::operator[](unsigned int index)
{
    return units[index];
}
