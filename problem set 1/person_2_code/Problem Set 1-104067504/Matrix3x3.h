
// COS30008, Problem Set 1, 2025

#pragma once

#include "Vector3D.h"

class Matrix3x3
{
private:
    
    Vector3D fRows[3];

public:
    
    Matrix3x3() noexcept;
    Matrix3x3( const Vector3D& aRow1, const Vector3D& aRow2, const Vector3D& aRow3 ) noexcept;

    Matrix3x3 operator*( const float aScalar ) const noexcept;
    Matrix3x3 operator+( const Matrix3x3& aOther ) const noexcept;

    Vector3D operator*( const Vector3D& aVector ) const noexcept;
    
    static Matrix3x3 getS( const float aX = 1.0f, const float aY = 1.0f ) noexcept;
    static Matrix3x3 getT( const float aX = 0.0f, const float aY = 0.0f ) noexcept;
    static Matrix3x3 getR( const float aAngleInDegree = 0.0f ) noexcept;
    
    const Vector3D& row( size_t aRowIndex ) const noexcept;
    const Vector3D column( size_t aColumnIndex ) const noexcept;

    const Vector3D& operator[]( size_t aRowIndex ) const noexcept;

    // Problem Set 1 features

    bool operator==( const Matrix3x3& aOther ) const noexcept;
    
    Matrix3x3 operator*( const Matrix3x3& aOther ) const noexcept;

    Matrix3x3 transpose() const noexcept;
    
    float det() const noexcept;
    bool hasInverse() const noexcept;
    Matrix3x3 inverse() const noexcept;
      
    friend std::ostream& operator<<( std::ostream& aOStream, const Matrix3x3& aMatrix );
};
