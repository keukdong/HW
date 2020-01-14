#pragma once

#include "AdditionalMath.h"
#include "Vector4.h"

struct Vector3;

__declspec(align(16)) struct Matrix4x4
{

public:
    union
    {
        struct
        {
            float _00, _01, _02, _03;
            float _10, _11, _12, _13;
            float _20, _21, _22, _23;
            float _30, _31, _32, _33;
        };
        Vector4 row[4];
    };

public:
    Matrix4x4();
    Matrix4x4(const Matrix4x4& m);
    Matrix4x4(const Vector4& m0, const Vector4& m1, const Vector4& m2, const Vector4& m3);
    Matrix4x4(const Vector4 m[4]);
    ~Matrix4x4() = default;

public:
    static Matrix4x4 Identity4x4;

public:
    Matrix4x4 operator = (const Matrix4x4& m);
    Matrix4x4 operator * (const Matrix4x4& m) const;
    Matrix4x4 operator * (const Vector4& v) const;
    void operator *= (const Matrix4x4& m);

    Vector4& operator[] (size_t index);
    const Vector4& operator[] (size_t index) const;

    Matrix4x4 Transpose();
    Matrix4x4 Inverse();

    Matrix4x4 Rotation(float x, float y, float z);
    Matrix4x4 RotationX(float x);
    Matrix4x4 RotationY(float y);
    Matrix4x4 RotationZ(float x);
    Matrix4x4 RotationAxis(float fAngle, Vector3 vAxis);

private:
    float determinant4x4() const;
};

