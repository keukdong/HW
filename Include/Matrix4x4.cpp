
#include "Matrix4x4.h"
#include "Vector3.h"


Matrix4x4 Matrix4x4::Identity4x4 = Matrix4x4(Vector4(1, 0, 0, 0), Vector4(0, 1, 0, 0), Vector4(0, 0, 1, 0), Vector4(0, 0, 0, 1));

Matrix4x4::Matrix4x4()
{
    row[0] = Vector4::Zero;
    row[1] = Vector4::Zero;
    row[2] = Vector4::Zero;
    row[3] = Vector4::Zero;
}

Matrix4x4::Matrix4x4(const Matrix4x4 & m)
{
    row[0] = m.row[0];
    row[1] = m.row[1];
    row[2] = m.row[2];
    row[3] = m.row[3];
}

Matrix4x4::Matrix4x4(const Vector4 & m0, const Vector4 & m1, const Vector4 & m2, const Vector4 & m3)
{
    row[0] = m0;
    row[1] = m1;
    row[2] = m2;
    row[3] = m3;
}

Matrix4x4::Matrix4x4(const Vector4 m[4])
{
    row[0] = m[0];
    row[1] = m[1];
    row[2] = m[2];
    row[3] = m[3];
}

Matrix4x4 Matrix4x4::operator=(const Matrix4x4 & m)
{
    row[0] = m.row[0];
    row[1] = m.row[1];
    row[2] = m.row[2];
    row[3] = m.row[3];

    return *this;
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4 & m) const
{
    return Matrix4x4();
}

Matrix4x4 Matrix4x4::operator*(const Vector4 & v) const
{
    return Matrix4x4();
}

void Matrix4x4::operator*=(const Matrix4x4 & m)
{
    *this = (*this)*m;
}

Vector4& Matrix4x4::operator[](size_t index)
{
    assert(index >= 0 && index < 4);
    return row[index];
}

const Vector4& Matrix4x4::operator[](size_t index) const
{
    assert(index >= 0 && index < 4);
    return row[index];
}

Matrix4x4 Matrix4x4::Transpose()
{
    return Matrix4x4();
}

Matrix4x4 Matrix4x4::Inverse()
{
    return Matrix4x4();
}

Matrix4x4 Matrix4x4::Rotation(float x, float y, float z)
{
    Matrix4x4 matRotX, matRotY, matRotZ;
    matRotX = (*this)*RotationX(x);
    matRotY = matRotX*RotationY(y);
    matRotZ = matRotY*RotationZ(z);
    return matRotZ;
}

Matrix4x4 Matrix4x4::RotationX(float x)
{
    return Matrix4x4();
}

Matrix4x4 Matrix4x4::RotationY(float y)
{
    return Matrix4x4();
}

Matrix4x4 Matrix4x4::RotationZ(float x)
{
    return Matrix4x4();
}

Matrix4x4 Matrix4x4::RotationAxis(float fAngle, Vector3 vAxis)
{
    return Matrix4x4();
}

float Matrix4x4::determinant4x4() const
{
    return 0.0f;
}
