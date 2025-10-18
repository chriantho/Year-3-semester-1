
// COS30008, tutorial 3, 2025

#include "Matrix3x3.h"

#include <cassert>
#include <cmath>
#include <numbers>

Matrix3x3::Matrix3x3() noexcept :
    fRows { Vector3D( 1.0f, 0.0f, 0.0f ),
            Vector3D( 0.0f, 1.0f, 0.0f ),
            Vector3D( 0.0f, 0.0f, 1.0f ) }
{}

Matrix3x3::Matrix3x3( const Vector3D& aRow1, const Vector3D& aRow2, const Vector3D& aRow3 ) noexcept :
    fRows { aRow1, aRow2, aRow3 }
{}

const Vector3D& Matrix3x3::row( size_t aRowIndex ) const noexcept
{
    assert( aRowIndex < 3 );
    
    return fRows[aRowIndex];
}

const Vector3D Matrix3x3::column( size_t aColumnIndex ) const noexcept
{
    assert( aColumnIndex < 3 );
    
    const Matrix3x3& M = *this;
    
    return Vector3D( M[0][aColumnIndex],
                     M[1][aColumnIndex],
                     M[2][aColumnIndex] );
}

const Vector3D& Matrix3x3::operator[]( size_t aRowIndex ) const noexcept
{
    return row( aRowIndex );
}

Matrix3x3 Matrix3x3::operator*( const float aScalar ) const noexcept
{
    const Matrix3x3& M = *this;

    return Matrix3x3( M[0] * aScalar, M[1] * aScalar, M[2] * aScalar );
}

Matrix3x3 Matrix3x3::operator+( const Matrix3x3& aOther  ) const noexcept
{
    const Matrix3x3& M = *this;

    return Matrix3x3( M[0] + aOther[0], M[1] + aOther[1], M[2] + aOther[2] );
}

Vector3D Matrix3x3::operator*( const Vector3D& aVector ) const noexcept
{
    const Matrix3x3& M = *this;

    return Vector3D( M[0].dot( aVector ), M[1].dot( aVector ), M[2].dot( aVector ) );
}

Matrix3x3 Matrix3x3::getS( const float aX, const float aY ) noexcept
{
    return Matrix3x3( Vector3D( aX, 0.0f, 0.0f ),
                      Vector3D( 0.0f, aY, 0.0f ),
                      Vector3D( 0.0f, 0.0f, 1.0f )
                    );
}

Matrix3x3 Matrix3x3::getT( const float aX, const float aY ) noexcept
{
    return Matrix3x3( Vector3D( 1.0f, 0.0f, aX ),
                      Vector3D( 0.0f, 1.0f, aY ),
                      Vector3D( 0.0f, 0.0f, 1.0f )
                    );
}

Matrix3x3 Matrix3x3::getR( const float aAngleInDegree ) noexcept
{
    float lRadTheta = aAngleInDegree * std::numbers::pi_v<float> / 180.0f;

    float lSinTheta = std::sin( lRadTheta );
    float lCosTheta = std::cos( lRadTheta );
    
    return Matrix3x3( Vector3D( lCosTheta, -lSinTheta, 0.0f ),
                      Vector3D( lSinTheta, lCosTheta, 0.0f ),
                      Vector3D( 0.0f, 0.0f, 1.0f ) );
}
