
#include "Vector2.h"


Vector2 Vector2::Zero = Vector2(0.f, 0.f);


Vector2::Vector2()
    : x(0.f)
    , y(0.f)
{
}

Vector2::Vector2(const Vector2 & _other)
{
    x = _other.x;
    y = _other.y;
}

Vector2::Vector2(float _x, float _y)
{
    x = _x;
    y = _y;
}

Vector2 Vector2::operator+(const Vector2 & _other)
{
    Vector2 result;
    result.x = x + _other.x;
    result.y = y + _other.y;
    return result;
}

void Vector2::operator+=(const Vector2 & _other)
{
    x += _other.x;
    y += _other.y;
}

Vector2 Vector2::operator-(const Vector2 & _other)
{
    Vector2 result;
    result.x = x - _other.x;
    result.y = y - _other.y;
    return result;
}

void Vector2::operator-=(const Vector2 & _other)
{
    x -= _other.x;
    y -= _other.y;
}

Vector2 & Vector2::operator=(const Vector2 & _other)
{
    x = _other.x;
    y = _other.y;

    return *this;
}

Vector2 Vector2::operator*(const Vector2 & _other)
{
    return Vector2(x*_other.x, y*_other.y);
}

Vector2 Vector2::operator*(float f)
{
    return Vector2(x*f, y*f);
}

Vector2 Vector2::operator/(const Vector2 & _other)
{
    if (_other.x == 0.f || _other.y == 0.f)
    {
        assert(false && " Vector2 divided by zero");
    }

    return Vector2(x/_other.x, y/_other.y);
}

Vector2 Vector2::operator/(float f)
{
    if (f == 0.f)
    {
        assert(false && " Vector2 divided by zero");
    }

    return Vector2(x / f, y / f);
}

bool Vector2::operator==(const Vector2 & _other) const
{
    return x == _other.x && y == _other.y ;
}

bool Vector2::operator!=(const Vector2 & _other) const
{
    return x != _other.x || y != _other.y ;
}

bool Vector2::IsNan() const
{
    return isnan(x+y);
}

float Vector2::GetSize() const
{
    return sqrtf(x * x + y * y );
}

float Vector2::GetRadianAngle(const Vector2& _other) const
{
    float fDot = x * _other.x + y * _other.y;
    return acosf(fDot / (this->GetSize() * _other.GetSize()));
}

float Vector2::GetAngle(const Vector2& _other) const
{
    return math::RadianToDegree(GetRadianAngle(_other));
}

float Vector2::GetDistance(const Vector2 & _other) const
{
    return sqrtf((x - _other.x)*(x - _other.x)
        + (y - _other.y)*(y - _other.y));
}

float Vector2::Dot(const Vector2 & _other) const
{
    return x * _other.x + y * _other.y;
}

Vector2 Vector2::Normalize() const
{
    float fSize = this->GetSize();

    if (fSize == 0.f)
        return Vector2::Zero;

    return Vector2(x/fSize, y/fSize);
}

Vector2 Vector2::Lerp(const Vector2 & _other, float fBias) const
{
    if (fBias >= 1.0f)
    {
        return *this;
    }

    if (fBias <= 0.f)
    {
        return _other;
    }

    Vector2 vSrc = *this;
    Vector2 vDst = _other;

    return vSrc * fBias + vDst * (1 - fBias);
}

Vector2 Vector2::Rotate(float fAngle) const
{
    float fSin = sinf(math::DegreeToRadian(fAngle));
    float fCos = cosf(math::DegreeToRadian(fAngle));

    return Vector2(fCos * x - fSin * y , fSin * x + fCos * y);
}
