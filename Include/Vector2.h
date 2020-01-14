
#pragma once

#include "AdditionalMath.h"


struct Vector2
{
    union
    {
public:
        struct
        {
            float x;
            float y;
        };
        struct
        {
            float r;
            float g;
        };
    };

    static Vector2 Zero;

public:
    Vector2();
    Vector2(const Vector2 &_other);
    Vector2(float _x, float _y);

    Vector2 operator+(const Vector2& _other);
    void operator+=(const Vector2& _other);

    Vector2 operator-(const Vector2& _other);
    void operator-=(const Vector2& _other);

    Vector2& operator =(const Vector2& _other);

    Vector2 operator *(const Vector2& _other);
    Vector2 operator *(float f);

    Vector2 operator /(const Vector2& _other);
    Vector2 operator /(float f);

    bool operator == (const Vector2& _other) const;
    bool operator != (const Vector2& _other) const;

public:
    bool IsNan() const;
    float GetSize() const;
    float GetRadianAngle(const Vector2& _other) const;
    float GetAngle(const Vector2& _other) const;
    float GetDistance(const Vector2& _other) const;
    float Dot(const Vector2& _other) const;

    Vector2 Normalize() const;
    Vector2 Lerp(const Vector2& _other, float fBias) const;
    Vector2 Rotate(float fAngle) const;
};
