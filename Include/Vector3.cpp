
#include "Vector3.h"


Vector3 Vector3::Zero = Vector3(0.f, 0.f, 0.f);


Vector3::Vector3()
    : x(0.f)
    , y(0.f)
    , z(0.f)
{
}

Vector3::Vector3(const Vector3 & v)
{
    x = v.x;
    y = v.y;
    z = v.z;
}

Vector3::Vector3(float _x, float _y, float _z)
{
    x = _x;
    y = _y;
    z = _z;
}

Vector3 Vector3::operator+(const Vector3& _other) const
{
    Vector3 result;
    result.x = x + _other.x;
    result.y = y + _other.y;
    result.z = z + _other.z;
    return result;
}

void Vector3::operator+=(const Vector3 & _other)
{
    x += _other.x;
    y += _other.y;
    z += _other.z;
}

Vector3 Vector3::operator-(const Vector3 & _other) const
{
    Vector3 result;
    result.x = x - _other.x;
    result.y = y - _other.y;
    result.z = z - _other.z;
    return result;
}

void Vector3::operator-=(const Vector3 & _other)
{
    x -= _other.x;
    y -= _other.y;
    z -= _other.z;
}

Vector3& Vector3::operator=(const Vector3 & _other)
{
    x = _other.x;
    y = _other.y;
    z = _other.z;

    return *this;
}

Vector3 Vector3::operator*(const Vector3 & _other) const
{
    return Vector3(x*_other.x, y*_other.y, z*_other.z);
}

Vector3 Vector3::operator*(float f) const
{
    return Vector3(x*f, y*f,z*f);
}

void Vector3::operator*=(float f)
{
    x *= f;
    y *= f;
    z *= f;
}

Vector3 Vector3::operator/(const Vector3 & _other) const
{
    return Vector3(x/_other.x, y/_other.y, z/_other.z);
}

Vector3 Vector3::operator/(float f) const
{
    if (f == 0.f)
    {
        assert(false && " Vector3 divided by zero");
    }

    return Vector3(x/f, y/f, z/f);
}

void Vector3::operator/=(float f)
{
    if (f == 0.f)
    {
        assert(false && " Vector3 divided by zero");
    }

    x /= f;
    y /= f;
    z /= f;
}

bool Vector3::operator==(const Vector3 & _other) const
{
    return x == _other.x && y == _other.y && z == _other.z;
}

bool Vector3::operator!=(const Vector3 & _other) const
{
    return x != _other.x || y != _other.y || z != _other.z;
}

Vector3 Vector3::Cross(const Vector3 & _other) const
{
    return Vector3(y*_other.z - z*_other.y,
        -(x*_other.z - z*_other.x), x*_other.y - y*_other.x);
}

float Vector3::Dot(const Vector3 & _other) const
{
    return x * _other.x + y * _other.y + z * _other.z;
}

Vector3 Vector3::Normalize() const
{
    float fSize = sqrtf(x * x + y * y + z * z);

    if (fSize == 0.f)
        return Vector3::Zero;

    return Vector3(x / fSize, y / fSize, z / fSize);
}

bool Vector3::IsNan() const
{
    return isnan(x+y+z);
}

float Vector3::GetSize() const
{
    return sqrtf(x * x + y * y + z * z);
}

float Vector3::GetRadianAngle(const Vector3 & _other) const
{
    float fDot = x * _other.x + y * _other.y + z * _other.z;
    return acosf(fDot / (this->GetSize() * _other.GetSize()));
}

float Vector3::GetAngle(const Vector3 & _other) const
{
    return math::RadianToDegree(GetRadianAngle(_other));
}

float Vector3::GetDistance(const Vector3 & _other)
{
    return sqrtf(x * x + y * y + z * z);
}

Vector3 Vector3::GetDirectionVector(const Vector3 & vDst)
{
    return Vector3(vDst.x - x, vDst.y - y, vDst.z - z).Normalize();
}

Vector3 Vector3::RotateX(float fAngle) const
{
    float fSin = sinf(math::DegreeToRadian(fAngle));
    float fCos = cosf(math::DegreeToRadian(fAngle));

    return Vector3(x, fCos * y - fSin * z, fSin * y + fCos * z);
}

Vector3 Vector3::RotateY(float fAngle) const
{
    float fSin = sinf(math::DegreeToRadian(fAngle));
    float fCos = cosf(math::DegreeToRadian(fAngle));

    return Vector3(fCos * x + fSin * z, y, -fSin * x + fCos * z);
}

Vector3 Vector3::RotateZ(float fAngle) const
{
    float fSin = sinf(math::DegreeToRadian(fAngle));
    float fCos = cosf(math::DegreeToRadian(fAngle));

    return Vector3(fCos * x - fSin * y, fSin * x + fCos * y , z);
}

Vector3 Vector3::Rotate(float fAngleX, float fAngleY, float fAngleZ) const
{
    Vector3 vResult = this->RotateX(fAngleX);
    vResult = vResult.RotateY(fAngleY);
    vResult = vResult.RotateZ(fAngleZ);

    return vResult;
}

Vector3 Vector3::RotateAround(const Vector3 & center, float fAngleX, float fAngleY, float fAngleZ) const
{
    Vector3 vMove = *this - center;
    vMove.Rotate(fAngleX, fAngleY, fAngleZ);
    vMove = vMove + center;
    return vMove;
}

Vector3 Vector3::Lerp(const Vector3 & _other, float fBias) const
{
    if (fBias >= 1.0f)
    {
        return *this;
    }

    if (fBias <= 0.f)
    {
        return _other;
    }

    Vector3 vSrc = *this;
    Vector3 vDst = _other;

    return vSrc *fBias + vDst *(1-fBias);
}

Vector3 Vector3::GetProjectVector(const Vector3 & vProjVector) const
{
    Vector3 vNormProj = vProjVector.Normalize();
    return vNormProj * (this->Dot(vNormProj));
}

Vector3 Vector3::GetReflectVector(const Vector3 & vNormalVector) const
{
    Vector3 vNorm = vNormalVector.Normalize();
    Vector3 vDir = Vector3(-x, -y, -z);

    float fLen = vDir.Dot(vNorm);

    Vector3 vReflect = -vDir + vNorm * 2 * fLen;
    return vReflect;
}

Vector3 operator-(const Vector3& vec)
{
    return Vector3(-vec.x, -vec.y, -vec.z);
}

