
// COS30008, Problem Set 1, 2025

#pragma once

#include "Vector2D.h"

#include <string>
#include <limits>

constexpr float eps = std::numeric_limits<float>::epsilon();

class Vector3D
{
private:

    Vector2D fBaseVector;
    float fW;
    
public:
        
    Vector3D( float aX = 1.0f, float aY = 0.0f, float aW = 1.0f ) noexcept;
    Vector3D( const Vector2D& aVector ) noexcept;
        
    float x() const noexcept { return fBaseVector.x(); }
    float y() const noexcept { return fBaseVector.y(); }
    float w() const noexcept { return fW; }

    float operator[]( size_t aIndex ) const noexcept;
    
    explicit operator Vector2D() const noexcept;
  
    Vector3D operator*( const float aScalar ) const noexcept;
    Vector3D operator+( const Vector3D& aOther ) const noexcept;
    float dot( const Vector3D& aOther ) const noexcept;
    
    friend std::ostream& operator<<( std::ostream& aOStream, const Vector3D& aVector );
    
    // Problem Set 1 extension
  
    bool operator==( const Vector3D& aOther ) const noexcept;
    
    std::string toString() const noexcept;
};
