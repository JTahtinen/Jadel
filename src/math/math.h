#pragma once
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat3.h"
#include <math.h>

#define MATH_PI 3.14159265
#define TO_RADIANS(angle) ((MATH_PI/180.f) * angle)

struct iPoint
{
    int x;
    int y;

    inline bool operator==(iPoint& other)
    {
        bool result = (x == other.x && y == other.y);
        return result;
    }

    inline bool operator!=(iPoint& other)
    {
        bool result = !(*this == other);
        return result;
    }
};

struct Quad
{
    Vec2 point0;
    Vec2 point1;
    Vec2 point2;
    Vec2 point3;
    Quad(Vec2 point0, Vec2 point1, Vec2 point2, Vec2 point3) 
        : point0(point0), point1(point1), point2(point2), point3(point3) {}
    Quad(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3) 
        : Quad({x0, y0}, {x1, y1}, {x2, y2}, {x3, y3}) {}
};

struct iRect
{
    int x, y;
    int w, h;
};

inline float clampf(float val, float min, float max)
{
    float result;
    if (val < min) result = min;
    else if (val > max) result = max;
    else result = val;
    return result;
}

inline float getXAtLinePoint(const Vec2 line, float y)
{
    if (line.y == 0) return line.x;
    float result = (line.x / line.y) * y;
    return result;
}

inline float getYAtLinePoint(const Vec2 line, float x)
{
    if (line.x == 0) return line.y;
    float result = (line.y / line.x) * x;
    return result;
}

inline int absINT(int val)
{
#if 0
    if (val < 0) return -val;
    return val;
#endif
    float result = val + (val < 0) * (2 * (-val));
    return result;
}

inline float absFloat(float val)
{
#if 0
    if (val < 0) return -val;
    return val;
#endif
    float result = val + (val < 0) * (2 * (-val));
    return result;
}

inline bool valIsBetween(float val, float min, float max)
{
    bool result = (val >= min && val <= max);
    return result;
}

inline bool vec2WithinRect(Vec2 vec, Vec2 point0, Vec2 point1)
{
    float minX;
    float minY;
    float maxX;
    float maxY;
    if (point0.x < point1.x)
    {
        minX = point0.x;
        maxX = point1.x;
    }
    else
    {
        minX = point1.x;
        maxX = point0.x;
    }
    if (point0.y < point1.y)
    {
        minY = point0.y;
        maxY = point1.y;
    }
    else
    {
        minX = point1.y;
        maxY = point0.y;
    }
    
    bool result = (valIsBetween(vec.x, minX, maxX) && valIsBetween(vec.y, minY, maxY));
    return result;
}

inline float getAngleOfVec2(Vec2 vec)
{
    float angleInRadians = atan2(vec.y, vec.x);
    float angleInDegrees = (angleInRadians / MATH_PI) * 180.0f;
    while(angleInDegrees < 0) angleInDegrees += 360.0f;
    while(angleInDegrees > 360.0f) angleInDegrees -= 360.0f;
    return angleInDegrees;
}

inline Vec2 createVec2FromAngle(float degrees)
{
    float rad = TO_RADIANS(degrees);
    Vec2 result = Vec2(cos(rad), sin(rad));
    return result;
}

inline int floorToInt(float val)
{
    int result = (int)(val - ((val < 0) * 1.0f));
    return result;
}

inline float fremainder(float value, float divider)
{
    if (divider == 0) return 0;
    float valFloor = (float)(floorToInt(value / divider));
    float result = value - valFloor * divider;
    return result;
}

inline int roundToInt(float val)
{
    int result = (val > 0) ? (int)(val + 0.5f) : (int)(val - 0.5f);
    return result;
}


inline void interpolate(float i0, float d0, float i1, float d1, float interval, float* buffer,
                        size_t bufferSize,
                        size_t* count)
{
    if (bufferSize == 0) return;
    if (count) *count = 0;
    if (interval == 0)
    {
        return;
    }
        if (i0 == i1)
    {
        buffer[*count++] = d0;
        return;
    }

    float finali0;
    float finali1;
    float finald0;
    float finald1;
    if (i0 < i1)
    {
        finali0 = i0;
        finali1 = i1;
        finald0 = d0;
        finald1 = d1;
    }
    else
    {
        finali0 = i1;
        finali1 = i0;
        finald0 = d1;
        finald1 = d0;
    }
    float dDiff = d1 - d0;
    float iDiff = i1 - i0;

    float a = dDiff / iDiff;
    float d = finald0;

    int valuesToWrite = (int)((finali1 - finali0) / interval);
    if (valuesToWrite > bufferSize - 1) valuesToWrite = bufferSize - 1;
   
    for (int i = 0; i <= valuesToWrite; ++i)
    {
        buffer[i] = d;
        d += a * interval;
        if (count) *count = *count + 1;
    }
}

inline void interpolate(float range, float interval, float* buffer, size_t bufferSize, size_t* count)
{
    *count = 0;
    if (range < interval) return;
    int valuesToWrite = (int)(range / interval);    
    if (valuesToWrite > bufferSize - 1) valuesToWrite = bufferSize - 1;
    

    for (int i = 0; i <= valuesToWrite; ++i)
    {
        float interp = (i / range) * interval;
        buffer[i] = interp;
        *count = *count + 1;
    }
}
