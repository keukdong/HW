
#pragma once

#include "AdditionalMath.h"


struct Vector3
{
public:
    union
    {
        struct
        {
            float x;
            float y;
            float z;
        };
        struct
        {
            float r;
            float g;
            float b;
        };
    };

    static Vector3 Zero;
    static Vector3 Axis[static_cast<size_t>(EAXIS::END)];

public:
    Vector3();
    Vector3(const Vector3 &v);
    Vector3(float _x, float _y, float _z);

    Vector3 operator+(const Vector3& _other) const;
    void operator+=(const Vector3& _other);

    Vector3 operator-(const Vector3& _other) const;
    void operator-=(const Vector3& _other);

    Vector3& operator =(const Vector3& _other);

    Vector3 operator *(const Vector3& _other) const;
    Vector3 operator *(float f) const;
    void operator *=(float f);

    Vector3 operator / (const Vector3& _other) const;
    Vector3 operator /(float f) const;
    void operator /=(float f);

    bool operator == (const Vector3& _other) const;
    bool operator != (const Vector3& _other) const;

public:
    Vector3 Cross(const Vector3& _other) const;
    float Dot(const Vector3& _other) const;
    Vector3 Normalize() const;

    bool IsNan() const;
    float GetSize() const;
    float GetRadianAngle(const Vector3& _other) const;
    float GetAngle(const Vector3& _other) const;
    float GetDistance(const Vector3& _other);

    Vector3 GetProjectVector(const Vector3 &vProjVector) const;
    Vector3 GetReflectVector(const Vector3& vNormalVector) const;
    Vector3 Lerp(const Vector3 &_other, float fBias) const;
    Vector3 GetDirectionVector(const Vector3& vDst);

    Vector3 RotateX(float fAngle) const;
    Vector3 RotateY(float fAngle) const;
    Vector3 RotateZ(float fAngle) const;
    Vector3 Rotate(float fAngleX, float fAngleY, float fAngleZ) const;
    Vector3 RotateAround(const Vector3& center, float fAngleX, float fAngleY, float fAngleZ) const;

    friend Vector3 operator-(const Vector3& vec);
};

Vector3 operator-(const Vector3& vec);
