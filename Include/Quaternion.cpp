#include "Quaternion.h"


Quaternion Quaternion::Zero = Quaternion();


Quaternion::Quaternion()
    : xi(0.f)
    , yj(0.f)
    , zk(0.f)
    , w(0.f)
{
}

Quaternion::Quaternion(float _w, float _x, float _y, float _z)
{
    w = _w;
    xi = _x;
    yj = _y;
    zk = _z;
}

Quaternion::Quaternion(float fAngle, const Vector3 & vector)
{
    xi = vector.x;
    yj = vector.y;
    zk = vector.z;
    w = fAngle;
}

Quaternion Quaternion::operator+(Quaternion q) const
{
    return Quaternion(w + q.w, xi + q.xi, yj + q.yj, zk + q.zk);
}

Quaternion Quaternion::operator-(Quaternion q) const
{
    return Quaternion(w - q.w, xi - q.xi, yj - q.yj, zk - q.zk);
}

Quaternion Quaternion::operator*(Quaternion q) const
{
    return Quaternion(
        -xi * q.xi - yj * q.yj - zk * q.zk + w * q.w,
        xi * q.w + w * q.xi + yj * q.zk - zk * q.yj ,
        yj * q.w + w * q.yj + zk * q.xi - xi * q.zk ,
        zk * q.w + w * q.zk + xi * q.yj - yj * q.xi
    );
}

Quaternion Quaternion::operator*(float f) const
{
    return Quaternion(w*f, xi*f, yj*f, zk*f);
}

Quaternion Quaternion::operator/(float f) const
{
    if (f == 0.f)
    {
        assert(false && " Quaternion divided by zero");
    }

    return Quaternion(w/f, xi/f, yj/f, zk/f);
}

Quaternion Quaternion::Conjugate() const
{
    return Quaternion(w, -xi, -yj, -zk);
}

Quaternion Quaternion::Inverse() const
{
    Quaternion Inverse = *this;
    Inverse = Inverse.Conjugate() / Inverse.Dot(Inverse);
    return Inverse;
}

bool Quaternion::operator==(Quaternion q) const
{
    return xi == q.xi && yj == q.yj && zk == q.zk && w == q.w;
}

bool Quaternion::operator!=(Quaternion q) const
{
    return xi != q.xi || yj != q.yj || zk != q.zk || w != q.w;
}

bool Quaternion::IsNan() const
{
    return isnan(xi + yj + zk + w);
}

float Quaternion::GetSize() const
{
    return sqrtf(xi * xi + yj * yj + zk * zk + w * w);
}

Quaternion Quaternion::Normalize() const
{
    float fSize = GetSize();

    if (fSize == 0.f)
        return Quaternion::Zero;

    return Quaternion(w/fSize, xi/fSize, yj/fSize, zk/ fSize);
}

float Quaternion::Dot(Quaternion q) const
{
    return (xi * q.xi + yj * q.yj + zk * q.zk + w * q.w);
}

Quaternion Quaternion::SLerp(const Quaternion& qDst, float fBias) const
{
    if (fBias <= 0.f)
        return *this;

    if (fBias >= 1.f)
        return qDst;

    Quaternion qNormSrc = this->Normalize();
    Quaternion qNormDst = qDst.Normalize();

    float fAngle = acosf(qNormSrc.Dot(qNormDst));

    if (fAngle < math::epsilon && fAngle > -math::epsilon)
    {
        return *this;
    }

    Quaternion qResult = qNormSrc * sinf(fAngle * (1 - fBias)) + qNormDst * sinf(fAngle * fBias);
    qResult = qResult / sinf(fAngle);

    return qResult;
}

Quaternion Quaternion::Rotate(const Vector3 & vAxis, float fAngle) const
{
    Vector3 vNormAxis = vAxis.Normalize();
    float fRad = math::DegreeToRadian(fAngle);
    Quaternion qRotate = Quaternion(cosf(fRad / 2), vNormAxis * sinf(fRad / 2));

    Quaternion qDst = qRotate * (*this) * qRotate.Conjugate();

    return qDst;
}

Vector3 Quaternion::QuaternionRotate(const Vector3 & vSrc, const Vector3 & vAxis, float fAngle)
{
    Quaternion qSrc = Quaternion(0, vSrc);

    Vector3 vNormAxis = vAxis.Normalize();
    float fRad = math::DegreeToRadian(fAngle);
    Quaternion qRotate = Quaternion(cosf(fRad / 2) , vNormAxis * sinf(fRad/2));

    Quaternion qDst = qRotate * qSrc * qRotate.Conjugate();

    return Vector3(qDst.xi, qDst.yj, qDst.zk);
}
