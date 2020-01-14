
#include "Vector4.h"


Vector4 Vector4::Zero = Vector4(0.f, 0.f, 0.f, 0.f);


Vector4::Vector4()
    : x(0.f)
    , y(0.f)
    , z(0.f)
    , w(0.f)
{
}

Vector4::Vector4(const Vector4 & v)
{
    x = v.x;
    y = v.y;
    z = v.z;
    w = v.w;
}

Vector4::Vector4(float _x, float _y, float _z, float _w)
{
    x = _x;
    y = _y;
    z = _z;
    w = _w;
}

Vector4 Vector4::operator+(const Vector4 & _other) const
{
    Vector4 result;
    result.x = x + _other.x;
    result.y = y + _other.y;
    result.z = z + _other.z;
    result.w = w + _other.w;
    return result;
}

void Vector4::operator+=(const Vector4 & _other)
{
    x += _other.x;
    y += _other.y;
    z += _other.z;
    z += _other.z;
}

Vector4 Vector4::operator-(const Vector4 & _other) const
{
    Vector4 result;
    result.x = x - _other.x;
    result.y = y - _other.y;
    result.z = z - _other.z;
    result.w = w - _other.w;
    return result;
}

void Vector4::operator-=(const Vector4 & _other)
{
    x -= _other.x;
    y -= _other.y;
    z -= _other.z;
    w -= _other.w;
}

Vector4 & Vector4::operator=(const Vector4 & _other)
{
    x = _other.x;
    y = _other.y;
    z = _other.z;
    w = _other.w;

    return *this;
}

Vector4 Vector4::operator*(const Vector4 & _other) const
{
    return Vector4(x*_other.x, y*_other.y, z*_other.z, w*_other.w);
}

Vector4 Vector4::operator*(float f) const
{
    return Vector4(x*f, y*f, z*f, w*f);
}

void Vector4::operator*=(float f)
{
    x *= f;
    y *= f;
    z *= f;
    w *= f;
}

Vector4 Vector4::operator/(const Vector4 & _other) const
{
    return Vector4(x/_other.x, y/_other.y, z/_other.z, w/_other.w);
}

Vector4 Vector4::operator/(float f) const
{
    if (f == 0.f)
    {
        assert(false && " Vector4 divided by zero");
    }

    return Vector4(x / f, y / f, z / f, w/f);
}

void Vector4::operator/=(float f)
{
    if (f == 0.f)
    {
        assert(false && " Vector4 divided by zero");
    }

    x /= f;
    y /= f;
    z /= f;
    w /= f;
}

float& Vector4::operator[](size_t index)
{
    assert(index >= 0 && index < 4);
    return element[index];
}

const float& Vector4::operator[](size_t index) const
{
    assert(index >= 0 && index < 4);
    return element[index];
}

bool Vector4::operator==(const Vector4 & _other) const
{
    return x == _other.x && y == _other.y && z == _other.z && w == _other.w;
}

bool Vector4::operator!=(const Vector4 & _other) const
{
    return x != _other.x || y != _other.y || z != _other.z || w != _other.w;
}

bool Vector4::IsNan() const
{
    return isnan(x+y+z+w);
}

float Vector4::GetSize() const
{
    return sqrtf(x * x + y * y + z * z + w * w);
}

float Vector4::Dot(const Vector4 & _other) const
{
    return x * _other.x + y * _other.y + z * _other.z + w * _other.w;
}

Vector4 Vector4::Normalize() const
{
    float fSize = this->GetSize();

    if (fSize == 0.f)
        return Vector4::Zero;

    return Vector4(x / fSize, y / fSize, z / fSize, w/fSize);
}

Vector4 Vector4::Lerp(const Vector4 & _other, float fBias) const
{
    if (fBias >= 1.0f)
    {
        return *this;
    }

    if (fBias <= 0.f)
    {
        return _other;
    }

    Vector4 vSrc = *this;
    Vector4 vDst = _other;

    return vSrc * fBias + vDst * (1 - fBias);
}
