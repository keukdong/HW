#pragma once

#include "AdditionalMath.h"
#include "Vector3.h"


struct Quaternion
{
public:
    float xi;
    float yj;
    float zk;
    float w;

    static Quaternion Zero;

public:
    Quaternion();
    Quaternion(float _w, float _x, float _y, float _z);
    Quaternion(float fAngle, const Vector3& vector);

public:
    Quaternion operator + (Quaternion q) const;
    Quaternion operator - (Quaternion q) const;
    Quaternion operator * (Quaternion q) const;
    Quaternion operator * (float f) const;
    Quaternion operator / (float f) const;
    Quaternion Conjugate() const;
    Quaternion Inverse() const;

    bool operator == (Quaternion q) const;
    bool operator != (Quaternion q) const;

public:
    bool IsNan() const;
    float GetSize() const;
    float Dot(Quaternion q) const;

    Quaternion Normalize() const;
    Quaternion SLerp(const Quaternion& qDst, float fBias) const;
    Quaternion Rotate(const Vector3& vAxis, float fAngle) const;

    static Vector3 QuaternionRotate(const Vector3& vSrc, const Vector3& vAxis, float fAngle);
};
