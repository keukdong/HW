
#pragma once

#include "AdditionalMath.h"


struct Vector4
{
public:
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
            float r;
            float g;
            float b;
            float a;
        };
        float element[4];
    };

public:
    static Vector4 Zero;

public:
    Vector4();
    Vector4(const Vector4 &v);
    Vector4(float _x, float _y, float _z, float _w);

    Vector4 operator+(const Vector4& _other) const;
    void operator+=(const Vector4& _other);

    Vector4 operator-(const Vector4& _other) const;
    void operator-=(const Vector4& _other);

    Vector4& operator =(const Vector4& _other);

    Vector4 operator *(const Vector4& _other) const;
    Vector4 operator *(float f) const;
    void operator *=(float f);

    Vector4 operator /(const Vector4& _other) const;
    Vector4 operator /(float f) const;
    void operator /=(float f);

    float& operator[](size_t index);
    const float& operator[](size_t index) const;

    bool operator == (const Vector4& _other) const;
    bool operator != (const Vector4& _other) const;

public:
    bool IsNan() const;
    float GetSize() const;
    float Dot(const Vector4& _other) const;

    Vector4 Normalize() const;
    Vector4 Lerp(const Vector4& _other, float fBias) const;
};

