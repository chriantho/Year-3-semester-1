
// COS30008, problem set 1, 2025

#include <iostream>
#include <cmath>
#include <numbers>

#define P1
#define P2

size_t gCount = 0;

#ifdef P1

#include "Vector3D.h"

void runP1()
{
    gCount++;
    
    constexpr float pi = std::numbers::pi_v<float>;

    Vector3D a( 1.0f, 2.0f, 3.0f );
    Vector3D aa( 1.00000003f, 2.00000008f, 3.00000005f );
    Vector3D b( pi, pi ,pi );
    Vector3D c( 1.23456789f, 9.876543210f, 12435.0987654321f );

    std::cout << "a == aa: " << (a == aa ? "true" : "false") << std::endl;
    std::cout << "a == b: " << (a == b ? "true" : "false") << std::endl;
    std::cout << "a == c: " << (a == c ? "true" : "false") << std::endl;
    std::cout << "b == c: " << (b == c ? "true" : "false") << std::endl;
    std::cout << "a == a: " << (a == a ? "true" : "false") << std::endl;
    std::cout << "b == b: " << (b == b ? "true" : "false") << std::endl;
    std::cout << "c == c: " << (c == c ? "true" : "false") << std::endl;

    std::cout << "Vector aa: " << aa.toString() << std::endl;
    std::cout << "Vector a: " << a.toString() << std::endl;
    std::cout << "Vector b: " << b.toString() << std::endl;
    std::cout << "Vector c: " << c.toString() << std::endl;
}

#endif

#ifdef P2

#include "Matrix3x3.h"

void runP2()
{
    gCount++;

    Matrix3x3 I;

    Matrix3x3 M1 = Matrix3x3::getR( 45.0f );
    Matrix3x3 M1T = M1.transpose();
    Matrix3x3 Prod = M1 * M1T;

    if ( Prod == I )
    {
        std::cout << "Matrix M1 is a rotation matrix." << std::endl;
    }
    else
    {
        std::cout << "Error." << std::endl;
    }

    std::cout << "det M = " << M1.det() << std::endl;

    Matrix3x3 M2 ( Vector3D( 25.0f, -3.0f, -8.0f ),
                   Vector3D( 6.0f, 2.0f, 15.0f ),
                   Vector3D( 11.0f, -3.0f, 4.0f ) );

    std::cout << "Test matrix M2:" << std::endl;
    std::cout << M2 << std::endl;

    // test multiplication

    std::cout << "M2 * M2 = " << std::endl;
    std::cout << M2 * M2 << std::endl;

    // test determinate

    std::cout << "det M2 = " << M2.det() << std::endl;

    // test hasInverse

    std::cout << "Does M2 have an inverse? " << (M2.hasInverse() ? "Yes" : "No") << std::endl;

    // test transpose
    std::cout << "transpose of M2:" << std::endl;
    std::cout << M2.transpose() << std::endl;

    // test inverse
    std::cout << "inverse of M2:" << std::endl;
    std::cout << M2.inverse() << std::endl;

    std::cout << "inverse of M2 * 45:" << std::endl;
    std::cout << M2.inverse() * 45.0f << std::endl;
}

#endif

int main( int argc, char* argv[] )
{
    int result = 0;
    
#ifdef P1

    runP1();

#endif

#ifdef P2

    runP2();

#endif

    if (!gCount)
    {
        std::cout << "No test enabled." << std::endl;
    }
    else
    {
        std::cout << gCount << " Test(s) completed." << std::endl;
    }

    return result;
}
